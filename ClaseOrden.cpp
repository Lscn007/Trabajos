#include <iostream>

using namespace std;

template<class T>
class Iterator
{
    T* it;
public:
    Iterator(T* itr) : it(itr) {}

    T* operator+(int a)
    { 
        return it+a;
    }

    T* operator-(int a)
    { 
        return it-a;
    }

    Iterator& operator++()
    {
        ++it;
        return *this;
    }

    Iterator operator++(int)
    { 
        Iterator temp = *this;
        ++it;
        return temp;
    }

    Iterator& operator--()
    { 
        --it;
        return *this;
    }

    void operator=(T value)
    {
        *it = value;
    }

    bool operator!=(const Iterator& itr) const
    {
        return it != itr.it;
    }

    T& operator*()
    {
        return *it;
    }
};


template <class T, class comparador>
class Orden
{
    comparador comp;
public:
    typedef Iterator<T> MyIt;

    void ordenar(MyIt a, MyIt b)
    {
        T tmp;
        for (MyIt i = b; i != a; --i)
        {
            for (MyIt v = a; v != i; ++v)
            {
                if (comp(*v, *(v + 1)))
                {
                    tmp = *v;
                    *v = *(v + 1);
                    *(v + 1) = tmp;
                }
            }
        }
    }
};

template<class T>
class Asc
{
public:
    bool operator()(T a, T b) const
    {
        return a > b; 
    }
};

template<class T>
class Dsc
{
public:
    bool operator()(T a, T b) const
    {
        return a < b; 
    }
};

void print(int* a, int tam) {
    cout << "[ ";
    for (int* i = a; i < a + tam; ++i) {
        cout << *i << " ";
    }
    cout << "]" << endl;
}

int main()
{
    int arr[10] = { 0 };
    int n = 10;
    for (int* i = arr; i < arr + 10; ++i, --n) {
        *i = n;
    }

    cout << "Antes de ser ordenado: ";
    print(arr, 10);

    Orden<int, Asc<int>> B;
    Orden<int, Asc<int>>::MyIt inicio(arr);
    Orden<int, Asc<int>>::MyIt fin(arr + 9);

    B.ordenar(inicio, fin);

    cout << "Después de ser ordenado: ";
    print(arr, 10);

    return 0;
}