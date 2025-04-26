#include <iostream>
using namespace std;

void mult(int (*p)[3][3]) {
    // A, B, C apuntan a las matrices dentro del arreglo tridimensional
    int (*A)[3] = p[0];  
    int (*B)[3] = p[1];  
    int (*C)[3] = p[2];  

    int* fila_A;         // Puntero para recorrer las filas de A
    int* col_B;          // Puntero para recorrer columnas de B
    int* fila_C;         // Puntero para recorrer las filas de C (resultado)

    // Recorremos las filas de A y de C al mismo tiempo
    for (fila_A = (int*)A, fila_C = (int*)C; fila_A < (int*)A + 9; fila_A += 3, fila_C += 3) {
        // Para cada fila de A, recorremos cada columna de B
        for (int* colB_start = (int*)B; colB_start < (int*)B + 3; colB_start++) {
            int suma = 0; // Acumulador para el producto escalar de A y B

            int* ptrA = fila_A;       // Puntero que recorre la fila en A
            int* ptrB = colB_start;   // Puntero que recorre la columna en B

            // Multiplicamos fila por columna
            for (int k = 0; k < 3; k++, ptrA++, ptrB += 3) {
                suma += (*ptrA) * (*ptrB); // Multiplicamos el elemento correspondiente y acumulamos
            }

            // Guardamos el resultado en la posición correcta de C
            *(fila_C + (colB_start - (int*)B)) = suma;
        }
    }
}

void print3D(int (*p)[3][3]) {
    int* ptr = (int*)p; 

    for (int z = 0; z < 3; z++) { 
        cout << "Matriz " << z << ":\n";
        for (int i = 0; i < 3; i++) {     // Tres filas por matriz
            for (int j = 0; j < 3; j++) { // Tres columnas por fila
                cout << *(ptr++) << " ";  // Imprimimos el valor y avanzamos el puntero
            }
            cout << endl;
        }
        cout << endl;
    }
}

int main() {
    int p[3][3][3] = {
        { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} },  // A -> p[0]
        { {9, 8, 7}, {6, 5, 4}, {3, 2, 1} },  // B -> p[1]
        { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} }   // C -> p[2] (resultado inicializado en 0)
    };

    mult(p);      
    print3D(p);   

    return 0;
}
