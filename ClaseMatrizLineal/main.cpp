#include <iostream>
#include "MatrizLineal.h"
using namespace std;

int main() {
    MatrizLineal matrizL(4,3); // Creamos una matriz de 4 filas y 3 columnas
    
    cout << "Matriz lineal: ";matrizL.printMatrizL();    // Imprimimos la matriz de manera LINEAL
    cout << "\nMatriz 2D: " << endl; matrizL.printMatriz2D();   // Imprimimos la matriz de manera BIDIMENSIONAL

    cout << "\n***ACCEDIENDO A LOS ELEMENTOS***" << endl;
    cout << "Elemento [0][0]: " <<matrizL.get(0,0) << endl;
    cout << "Elemento [1][1]: " <<matrizL.get(1,1) << endl;
    cout << "Elemento [2][2]: " <<matrizL.get(2,2) << endl;
    cout << "Elemento [3][2]: " <<matrizL.get(3,2) << endl;

    cout << "***INSERTANDO ELEMENTOS***" << endl;
    cout << "Insertando en [0][0]... ", matrizL.set(0,0,12);
    cout << "\nInsertando en [1][1]... "; matrizL.set(1,1,9);
    cout << "\nInsertando en [2][2]... "; matrizL.set(2,2,5);
    cout << "\nInsertando en [3][2]... "; matrizL.set(3,2,1);

    cout << "\n***ACCEDIENDO A LOS ELEMENTOS DESPUES DE MODIFICARLOS***" << endl;
    cout << "Elemento [0][0]: " <<matrizL.get(0,0) << endl;
    cout << "Elemento [1][1]: " <<matrizL.get(1,1) << endl;
    cout << "Elemento [2][2]: " <<matrizL.get(2,2) << endl;
    cout << "Elemento [3][2]: " <<matrizL.get(3,2) << endl;

    cout << "Matriz lineal: ";matrizL.printMatrizL();    
    cout << "\nMatriz 2D: " << endl; matrizL.printMatriz2D();

    int valor = matrizL(2,1);          // El operador se comporta como getter ,forma equivalente de llamar a la función -> int valor = matrizL.operator()(2,1);
    cout << "\n" << valor << endl;  
    matrizL(2,1) = 100;                // El operador se comporta como setter
    matrizL.printMatriz2D();

    return 0;
}