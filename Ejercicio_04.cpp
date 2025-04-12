/*Crea un array de enteros en donde la mitad sean pares ordenados y la otra
mitad impares ordenados. Usando punteros crea una funcion (merge) para 
ordenar los elementos del array*/

#include <iostream>
using namespace std;

void merge(int* p, int* q, int* end) {
    for (int* i = p; i < q; i++ ) { // Iteramos en la primera mitad.
        for (int* j = q; j < end; j++) { // Iteramos en la segunda mitad.
            if (*i > *j) {
                swap(*i, *j);
                while(*j > *(j + 1)) { // Comparamos el número en su nueva posicion con los de la seguna mitad.
                    swap(*j, *(j + 1));
                    j++; // Si el número se mueve al puntero tambien.
                }
            }
        } 
    }
} 

void printPtr(int* ptr, const int& size) {
    cout << "[ ";
    for (int i{0}; i < size; i++) {
        cout << ptr[i] << " ";
    }
    cout << "]";
}

int main() {
    int array[] = {8,24,36,5,17,25};
    int* p = array;
    int* q = &array[3];
    int* end = &(array[((q - p) * 2) - 1]); // Forma equivalente: p + ((q - p) * 2) - 1.
    int size = end - p + 1;

    cout << "Unsorted array: "; printPtr(array, size);
    cout << "\nSorted array: "; merge(p, q, end); printPtr(array, size);

}