#ifndef MATRIZLINEAL_H
#define MATRIZLINEAL_H

class MatrizLineal {
    private:
        int* vec;
        int dx, dy;
    public:
        MatrizLineal(int, int);
        
        ~MatrizLineal();

        int get(int, int);
        
        void set(int, int, int);

        int& gs(int, int);

        int& operator()(int, int);

        void printMatrizL();

        void printMatriz2D();

};

#endif