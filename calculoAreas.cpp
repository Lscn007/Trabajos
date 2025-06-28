#include <iostream>
#include <iomanip>
using namespace std;

// Tipo de puntero a función
typedef float (*FuncionArea)(float, float);

// Funciones para cada figura
float areaCirculo(float radio, float) {
    const float pi = 3.14;
    return pi * radio * radio;
}

float areaRectangulo(float base, float altura) {
    return base * altura;
}

float areaTriangulo(float base, float altura) {
    return (base * altura) / 2;
}

float areaCuadrado(float lado, float) {
    return lado * lado;
}

// Función que calcula y muestra todas las áreas
void ejecutar(FuncionArea areaFroma[], float datos[][2], const char* nombres[]) {
    cout << fixed << setprecision(2);

    for (int i = 0; i < 4; i++) {
        float a = datos[i][0];
        float b = datos[i][1];
        float resultado = areaFroma[i](a, b);

        cout << "Área de " << nombres[i] << ": " << resultado << " m2" << endl;
    }
}

int main() {
    // Arreglo de funciones
    FuncionArea areas[] = {areaCirculo, areaRectangulo, areaTriangulo, areaCuadrado};

    // Matriz de parámetros para cada figura
    float valores[][2] = {
        {3.5, 0},   // Circulo
        {6, 2},     // Rectangulo
        {8, 9},     // Triangulo
        {5, 3}      // Cuadrado
    };

    // Nombres para las figuras
    const char* nombres[] = {"circulo", "rectángulo", "triangulo", "cuadrado"};

    // Ejecutar el cálculo y mostrar los resultados
    ejecutar(areas, valores, nombres);

    return 0;
}
