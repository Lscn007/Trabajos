#include <iostream>
#include <conio.h> // Libreria para getch que lee las teclas sin necesidad del enter
using namespace std;

void drawBoard(char** board) {
    for (char** fila = board; fila < board + 3; fila++) {
        cout << "[ ";
        for (char* columna = *fila; columna < *fila + 3; columna++) {
            cout << *columna << " ";
        }
        cout << "]\n";
    }
}

// Inicializa los elementos del array (matriz/tablero 3x3)
void putElements(char** board, char elements[]) {
    int k = 0; // Índice para los elementos
    for (char** fila = board; fila < board + 3; fila++) {
        *fila = new char[3];
        for (char* columna = *fila; columna < *fila + 3; columna++) {
            if (k == 8) {
                *columna = ' '; // Espacio vacio
            } else {
                *columna = *(elements + k);
                k++;
            }
        }
    }
}

// Función para comparar el estafo el tablero despues de cada movimiento con la configuración ganadora
bool winner(char** board) {
    // Configuración ganadora del tablero
    char target[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', ' '}
    };

    char** board_fila = board;
    for (int i = 0; i < 3; i++, board_fila++) {
        char* board_columna = *board_fila;
        for (int j = 0; j < 3; j++, board_columna++) {
            if (*board_columna != target[i][j]) {
                return false; // Algun elemento no coindice
            }
        }
    }
    return true; // Todos los elementos coinciden con la configuración ganadora
}

void moveEmptySpace(char** board) {
    char** fila_ptr = board;
    char* columna_ptr = nullptr;
    char* espacio_ptr = nullptr;
    int x = 0, y = 0;

    // Buscar la posición de la casilla vacía (' ')
    for (; fila_ptr < board + 3; fila_ptr++, x++) {
        columna_ptr = *fila_ptr;
        for (y = 0; y < 3; y++, columna_ptr++) {
            if (*columna_ptr == ' ') {
                espacio_ptr = columna_ptr;
                break;
            }
        }
        if (espacio_ptr != nullptr) {
            break;
        }
    }

    // Captura la entrada del usuario por _getch()
    char key = _getch(); // Espera a que se presione una tecla
    
    // Procesa las teclas especiales como las flechas
    if (key == 0 || key == 224) {
        key = _getch(); // Lee el código de la flecha
    }

    switch (key) {
        case 72: // Arriba
            if (x > 0) {
                swap(*columna_ptr, *(*(board + (x - 1)) + y));
            }
            break;
        case 80: // Abajo
            if (x < 2) {
                swap(*columna_ptr, *(*(board + (x + 1)) + y));
            }
            break;
        case 75: // Izquierda
            if (y > 0) {
                swap(*columna_ptr, *(*fila_ptr + (y - 1)));
            }
            break;
        case 77: // Derecha
            if (y < 2) {
                swap(*columna_ptr, *(*fila_ptr + (y + 1)));
            }
            break;
        default:
            cout << "Tecla no válida. Usa las flechas del teclado." << endl;
            break;
    }
}

// Función principal que ejecuta el juego
void run(char** board, char elements[]) {
    putElements(board, elements);
    drawBoard(board);

    // Bucle del juego que se actualiza después de cada movimiento de la casilla
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

    cout << "\n1. Play\n2. Show instructions\n3. Exit\nElije una opcion: ";
    cin >> option;

    while (option != 3) {
        cout << "\n1. Play\n2. Show instructions\n3. Exit\nElije una opcion: ";
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
    }
} 


int main() {
    // Array objetivo del juego (estado ordenado)
    char elements[] = {'8','6','7','2','5','4','3','1'};
    char** board = new char*[3];

    putElements(board, elements);
    menu(board, elements);

    // Liberando memoria desde atras hacia adelante
    for (char** fila = board; fila < board + 3; fila++) {
        delete[] *fila;
    }
    delete[] board;

    return 0;
}