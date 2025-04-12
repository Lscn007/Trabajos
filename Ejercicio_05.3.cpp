#include <iostream>
#include <conio.h>
using namespace std;

void drawBoard(char** board) {
    for (int i = 0; i < 3; i++) {
        cout << "[ ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << "]\n";
    }
}

// Función para desordenar de forma fija (controlada)
void unsort(char elements[]) {
    // Este patrón fijo intercambia el elemento en la posición 2 con todos los demás.
    // Es determinista, pero garantiza que la configuración inicial sea diferente.
    for (int i = 0; i < 8; i++) {
        swap(elements[2], elements[i]);
    }
}

// Coloca los elementos del array en el tablero 3x3
void putElements(char** board, char elements[]) {
    int k = 0; // Índice para los elementos
    for (int i = 0; i < 3; i++) {
        board[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            if (k >= 8) {
                board[i][j] = ' ';  // Espacio vacío
            } else {
                board[i][j] = elements[k];
                k++; 
            }
        }
    }
}

// Función para comparar el tablero actual con el estado ganador
bool winner(char** board) {
    // Configuración ganadora fija
    char target[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', ' '}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != target[i][j]) {
                return false;  // Algún elemento no coincide
            }
        }
    }
    return true;  // Todos los elementos son iguales
}

// Mueve la casilla vacía usando las flechas del teclado
void moveEmptySpace(char** board) {
    int x = -1, y = -1;

    // Busca la posición de la casilla vacía (espacio)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                x = i;
                y = j;
                break;
            }
        }
        if (x != -1) break;
    }

    // Captura la entrada del usuario con _getch()
    char key = _getch();  // Espera a que se presione una tecla

    // Procesa las teclas especiales (flechas)
    if (key == 0 || key == 224) {
        key = _getch();  // Lee el código de la flecha
    }

    switch (key) {
        case 72: // Flecha arriba
            if (x > 0) {
                swap(board[x][y], board[x - 1][y]);
            }
            break;
        case 80: // Flecha abajo
            if (x < 2) {
                swap(board[x][y], board[x + 1][y]);
            }
            break;
        case 75: // Flecha izquierda
            if (y > 0) {
                swap(board[x][y], board[x][y - 1]);
            }
            break;
        case 77: // Flecha derecha
            if (y < 2) {
                swap(board[x][y], board[x][y + 1]);
            }
            break;
        default:
            cout << "Tecla no válida. Usa las flechas del teclado." << endl;
            break;
    }
}

// Función que ejecuta el juego
void run(char** board, char elements[]) {
    // Primero, desordena los elementos y actualiza el tablero
    unsort(elements);
    putElements(board, elements);
    drawBoard(board);

    // Bucle de juego: se actualiza después de cada movimiento
    while (!winner(board)) {
        cout << "Usa las flechas para mover la casilla vacía." << endl;
        moveEmptySpace(board);
        drawBoard(board);
    }

    cout << "¡Felicidades! Has ganado." << endl;
}

void menu(char **board, char elements[]) {
    cout << "WELCOME PLAYER" << endl;
    int option;

    do {
        cout << "\n1. Play\n2. Show instructions\n3. Exit\nChose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                run(board, elements);
                break;
            case 2:
                cout << "\nEl objetivo del juego es ordenar el tablero así:" << endl;
                cout << "[ 1 2 3 ]\n[ 4 5 6 ]\n[ 7 8   ]\n";
                break;
            case 3:
                cout << "\nSaliendo..." << endl;
                break;
            default:
                cout << "\nOpción inválida. Por favor, elije 1, 2 o 3\n";
                break;
        }
    } while (option != 3);
}

int main() {
    // Este array es el estado ordenado (objetivo)
    char elements[] = {'1','2','3','4','5','6','7','8'};

    // Reservamos memoria para el tablero
    char** board = new char*[3];
    
    // Inicializamos el tablero con la configuración ordenada
    putElements(board, elements);

    menu(board, elements);

    // Liberar memoria (se recomienda liberar cada fila antes de liberar el array de punteros)
    for (int i = 0; i < 3; i++) {
        delete [] board[i];
    }
    delete [] board;

    return 0;
}