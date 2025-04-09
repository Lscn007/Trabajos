#include <iostream>
#include <bitset>

using namespace std;

// Convierte un número decimal a su representación en n bits (complemento a 2)
int aBinario(int num, int n) {
    if (num < 0) {
        num = (1 << n) + num; 
    }
    return num;
}

// Multiplicación de Booth
int multiplicacionBooth(int M, int Q, int n) {
    // M y Q deben estar ya convertidos a su representación en n bits (dos complementos)
    int A = 0;       // Acumulador (n bits)
    int Q_1 = 0;     // Bit auxiliar
    int totalBits = 2 * n + 1; // Registro completo: A (n bits), Q (n bits) y Q_1 (1 bit)

    for (int i = 0; i < n; i++) {
        int bitQ0 = Q & 1;  // Bit menos significativo de Q

        // Según los valores de (Q0, Q_1) se decide la operación en A
        if (bitQ0 == 1 && Q_1 == 0) {
            // A = A - M en aritmética de n bits
            A = (A - M) & ((1 << n) - 1);
        } else if (bitQ0 == 0 && Q_1 == 1) {
            // A = A + M en aritmética de n bits
            A = (A + M) & ((1 << n) - 1);
        }

        // Se arma el registro completo combinando A, Q y Q_1
        int registro = (A << (n + 1)) | (Q << 1) | Q_1;

        /* Se realiza el corrimiento aritmético a la derecha sobre el registro de (2*n+1) bits
        Para ello, se toma el bit de signo (bit más significativo del registro) y se repite*/
        int signo = (registro >> (totalBits - 1)) & 1;
        registro = (registro >> 1) | (signo << (totalBits - 1));

        // Se extraen nuevamente A, Q y Q_1 del registro actualizado
        A = (registro >> (n + 1)) & ((1 << n) - 1);
        Q = (registro >> 1) & ((1 << n) - 1);
        Q_1 = registro & 1;
    }

    int producto = (A << n) | Q;
    int totalBitsProducto = 2 * n;
    
    if (producto & (1 << (totalBitsProducto - 1))) { // Si el bit de signo es 1...
        producto = producto - (1 << totalBitsProducto);
    }

    return producto;
}

int main() {
    int n;
    cout << "Ingrese la cantidad de bits: ";
    cin >> n;

    int multiplicando, multiplicador;
    cout << "Ingrese el multiplicando (decimal): ";
    cin >> multiplicando;
    cout << "Ingrese el multiplicador (decimal): ";
    cin >> multiplicador;

    int M = aBinario(multiplicando, n);
    int Q = aBinario(multiplicador, n);

    int resultado = multiplicacionBooth(M, Q, n);
    cout << "El resultado de la multiplicación es: " << resultado << endl;

    return 0;
}

