#include <iostream>
#include <iomanip>
using namespace std;

// Tipo de puntero a función
typedef float (*FuncionArea)(float, float);

// Funciones para cada figura
float areaCuadrado(float lado, float) {
    return lado * lado;
}

float areaTriangulo(float base, float altura) {
    return (base * altura) / 2;
}

float areaCirculo(float radio, float) {
    const float pi = 3.14;
    return pi * radio * radio;
}

float areaRectangulo(float base, float altura) {
    return base * altura;
}

// Función que calcula y muestra todas las áreas
void calcularYMostrar(FuncionArea formas[], float datos[][2], const char* etiquetas[], int total) {
    cout << fixed << setprecision(2);

    for (int i = 0; i < total; i++) {
        float a = datos[i][0];
        float b = datos[i][1];
        float resultado = formas[i](a, b);

        cout << "Área de " << etiquetas[i] << ": " << resultado << " m2" << endl;
    }
}

int main() {
    // Cantidad total de figuras
    int totalFiguras = 4;

    // Arreglo de funciones
    FuncionArea areas[] = {
        areaCuadrado,
        areaTriangulo,
        areaCirculo,
        areaRectangulo
    };

    // Parámetros correspondientes a cada figura
    float valores[][2] = {
        {3.5, 0},   // Cuadrado
        {6, 2},     // Triángulo
        {4, 0},     // Círculo
        {5, 3}      // Rectángulo
    };

    // Nombres para las figuras
    const char* nombres[] = {
        "cuadrado",
        "triángulo",
        "círculo",
        "rectángulo"
    };

    // Ejecutar el cálculo y mostrar los resultados
    calcularYMostrar(areas, valores, nombres, totalFiguras);

    return 0;
}
