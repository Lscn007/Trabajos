#include <iostream>
#include "MatrizLineal.h"
using namespace std;

MatrizLineal::MatrizLineal(int _dx, int _dy) : dx{_dx}, dy{_dy} {
    vec = new int[dx * dy];   // vec es un atributo de la clase por eso puedo usarlo en cualquier función miemrbro - Matriz conceptual
    int* end = vec + dx * dy; // El puntero end es una varibale LOCAL, por eso no podre usarla fuera de su ámbito
    int j = 0;
    for (int* i = vec; i < end; i++, j++) {
        *i = 1 + j;
    }
}

MatrizLineal::~MatrizLineal() {
    delete[] vec;
}

int MatrizLineal::get(int x, int y) {
    return *(vec + (x * dy + y)); // Fórmula de mapeo que convierta un par de coordenadas (fila, columna) a un índice plano del array.
}

void MatrizLineal::set(int x, int y, int v) {
    *(vec + (x * dy + y)) = v;
}

int& MatrizLineal::gs(int x, int y) { 
    return *(vec + (x * dy + y));      // Retorna una referencia(alias) al elemento en la posición (x, y)
}

int& MatrizLineal::operator()(int x, int y) {
    return *(vec + (x * dy + y));      // Retorna una referencia(alias) al elemento en la posición (x, y)
} 

void MatrizLineal::printMatrizL() {
    int* begin = vec;
    int* end = vec + dx * dy;

    cout << "[ ";
    for (int* i = begin; i < end; i++) {
        cout << *i << " ";
    }
    cout << "]";
}

void MatrizLineal::printMatriz2D() {
    int* begin = vec;
    int* end = vec + dx * dy;
    int j = 0;

    cout << "[ ";
    for (int* i = begin; i < end; i++) {
        cout << *i << " ";
        j++;
        if (j % dx != 0 && j % dy == 0 ) {
            cout << "]\n[ ";
        }
    }
    cout << "]";
}
