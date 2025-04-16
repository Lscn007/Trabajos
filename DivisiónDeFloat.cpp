#include <iostream>
#include <cstdint>
#include <cstring>
#include <cmath>  // Para usar NAN

// Descomponer un float en signo, exponente y mantisa
void descomponer(float num, uint32_t &signo, uint32_t &exponente, uint32_t &mantisa) {
    uint32_t bits;
    std::memcpy(&bits, &num, sizeof(bits));
    signo = bits >> 31;
    exponente = (bits >> 23) & 0xFF;
    mantisa = bits & 0x7FFFFF;
}

// Recomponer un float desde signo, exponente y mantisa
float componer(uint32_t signo, uint32_t exponente, uint32_t mantisa) {
    uint32_t bits = (signo << 31) | (exponente << 23) | mantisa;
    float resultado;
    std::memcpy(&resultado, &bits, sizeof(resultado));
    return resultado;
}

// División emulada en IEEE 754
float dividir(float a, float b) {
    // Casos especiales
    if (b == 0.0f) {
        if (a == 0.0f) 
            return NAN;
        return (a > 0.0f) ? componer(0, 0xFF, 0) : componer(1, 0xFF, 0); // Infinito
    }
    if (a == 0.0f) 
        return 0.0f;

    // Descomponer a y b 
    uint32_t signoA, expA, mantA;
    uint32_t signoB, expB, mantB;
    descomponer(a, signoA, expA, mantA);
    descomponer(b, signoB, expB, mantB);

    // Calcular el signo del resultado
    uint32_t signoR = signoA ^ signoB;
    
    // Ajuste del exponente, remueve bias, resta y vuelve a sumar bias
    int32_t expR = (int(expA) - 127) - (int(expB) - 127) + 127;
    
    // Agregar el bit implícito (1) a la mantisa (para números normalizados)
    uint32_t mA = mantA | (1 << 23);
    uint32_t mB = mantB | (1 << 23);
    
    // Extender la precisión del numerador al desplazar mA (24 bits) 23 posiciones
    uint64_t num = (uint64_t)mA << 23;
    uint32_t mantR = num / mB;  // División entera de las mantisas
    
    // Normalización del resultado
    // Si la mantisa tiene más de 24 bits, se corrige desplazándola a la derecha.
    if (mantR >= (1u << 24)) {
        mantR >>= 1;
        expR++;
    }
    // Si la mantisa no tiene el bit 23 activo, se desplaza a la izquierda.
    else if ((mantR & (1u << 23)) == 0) {
        mantR <<= 1;
        expR--;
    }
    
    // Verificar overflow o underflow del exponente
    if (expR >= 255)
        return componer(signoR, 0xFF, 0);  // Infinito
    if (expR <= 0)
        return componer(signoR, 0, 0);     // Cero (tratando subnormales de forma simplificada)
    
    // Eliminar el bit implícito (mantisa de 23 bits)
    mantR &= 0x7FFFFF;
    return componer(signoR, expR, mantR);
}

int main() {
    float a, b;
    std::cout << "Ingresa el valor de A (dividendo): ";
    std::cin >> a;
    std::cout << "Ingresa el valor de B (divisor): ";
    std::cin >> b;

    float resultado = dividir(a, b);
    std::cout << "\nResultado emulado (float): " << resultado << std::endl;

    // Conversión a entero (truncado)
    int resultadoEntero = static_cast<int>(resultado);
    std::cout << "Resultado como entero (truncado): " << resultadoEntero << std::endl;

    // División nativa para comparación
    float nativo = a / b;
    std::cout << "\nResultado nativo (float): " << nativo << std::endl;

    return 0;
}