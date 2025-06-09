#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

// Funciones comparadoras con punteros a función
bool myGreater(int a, int b) { return a > b; }
bool myLess(int a, int b) { return a < b; }

// Functores 
struct LessFunctor {
    bool operator()(int a, int b) const { return a < b; }
};

struct GreaterFunctor {
    bool operator()(int a, int b) const { return a > b; }
};

// Functores inline
inline struct LessInline {
    bool operator()(int a, int b) const { return a < b; }
} lessInline;

inline struct GreaterInline {
    bool operator()(int a, int b) const { return a > b; }
} greaterInline;

// Clase base abstracta para polimorfismo
class Compare {
public:
    virtual bool operator()(int a, int b) const = 0;  // método virtual puro
    virtual ~Compare() = default;
};

// Implementación para polimorfismo
class LessCompare : public Compare {
public:
    bool operator()(int a, int b) const override { return a < b; }
};

class GreaterCompare : public Compare {
public:
    bool operator()(int a, int b) const override { return a > b; }
};

// Generar vector con números aleatorios
vector<int> generateVector(size_t size) {
    vector<int> data(size);
    mt19937 randGen(12345);  // Seed fijo para que siempre genere la misma secuencia

    for (int& x : data) {
        x = randGen();
    }
    return data;
}

// 1. Quicksort usando < y >
void quicksortAsc(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quicksortAsc(arr, left, j);
    quicksortAsc(arr, i, right);
}

void quicksortDesc(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i] > pivot) i++;
        while (arr[j] < pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quicksortDesc(arr, left, j);
    quicksortDesc(arr, i, right);
}

// 2. Quicksort usando punteros a función
void quicksort(vector<int>& arr, int left, int right, bool (*comp)(int, int)) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (comp(arr[i], pivot)) i++;
        while (comp(pivot, arr[j])) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    quicksort(arr, left, j, comp);
    quicksort(arr, i, right, comp);
}

// 3. Quicksort usando functores con o sin inline
template <typename Compare>
void quicksort(vector<int>& arr, int left, int right, Compare comp) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (comp(arr[i], pivot)) i++;
        while (comp(pivot, arr[j])) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quicksort(arr, left, j, comp);
    if (i < right) quicksort(arr, i, right, comp);
}

// 4. Quicksort usando polimorfismo
void quicksort(vector<int>& arr, int left, int right, const Compare& comp) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (comp(arr[i], pivot)) i++;
        while (comp(pivot, arr[j])) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) quicksort(arr, left, j, comp);
    if (i < right) quicksort(arr, i, right, comp);
}

int main() {
    const size_t size = 500000; // Tamaño reducido para comparaciones estables
    cout << "Generando vector de tamaño " << size << "...\n";

    // Vector original (Mismo vector para todas las funciones)
    vector<int> original = generateVector(size);
    
    // Hacer 3 pruebas en cada una y promediar el tiempo
    const int numPruebas = 3;
    
    // 1. Usando < y >
    long long tiempo1 = 0;
    for (int i = 0; i < numPruebas; i++) {
        vector<int> v1 = original;
        auto start = chrono::high_resolution_clock::now();
        quicksortAsc(v1, 0, (int)v1.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        tiempo1 += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    cout << "Quicksort Ascendente (< y >) promedio: " << tiempo1 / numPruebas << " μs\n";

    // 2. Usando punteros a función
    long long tiempo2 = 0;
    for (int i = 0; i < numPruebas; i++) {
        vector<int> v2 = original;
        auto start = chrono::high_resolution_clock::now();
        quicksort(v2, 0, (int)v2.size() - 1, myLess);
        auto end = chrono::high_resolution_clock::now();
        tiempo2 += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    cout << "Quicksort con punteros a función promedio: " << tiempo2 / numPruebas << " μs\n";

    // 3. Usando functores sin inline
    long long tiempo3 = 0;
    for (int i = 0; i < numPruebas; i++) {
        vector<int> v3 = original;
        auto start = chrono::high_resolution_clock::now();
        quicksort(v3, 0, (int)v3.size() - 1, LessFunctor{});
        auto end = chrono::high_resolution_clock::now();
        tiempo3 += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    cout << "Quicksort con functor (sin inline) promedio: " << tiempo3 / numPruebas << " μs\n";

    // 4. Usando functores inline
    long long tiempo4 = 0;
    for (int i = 0; i < numPruebas; i++) {
        vector<int> v4 = original;
        auto start = chrono::high_resolution_clock::now();
        quicksort(v4, 0, (int)v4.size() - 1, lessInline);
        auto end = chrono::high_resolution_clock::now();
        tiempo4 += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    cout << "Quicksort con functor (inline) promedio: " << tiempo4 / numPruebas << " μs\n";

    // 5. Usando polimorfismo
    long long tiempo5 = 0;
    for (int i = 0; i < numPruebas; i++) {
        vector<int> v5 = original;
        LessCompare lessObj;
        auto start = chrono::high_resolution_clock::now();
        quicksort(v5, 0, (int)v5.size() - 1, lessObj);
        auto end = chrono::high_resolution_clock::now();
        tiempo5 += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    cout << "Quicksort con polimorfismo promedio: " << tiempo5 / numPruebas << " μs\n";

    return 0;
}