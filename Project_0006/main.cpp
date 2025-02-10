#include <iostream>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    #include <unistd.h>
    #include <termios.h>
    #define CLEAR_COMMAND "clear"
#endif

void drawCover(int &n) {
    //std::system(CLEAR_COMMAND);  // Borra pantalla
    std::cout << "\x1B[H";        // Mueve cursor al inicio

    std::cout << "\x1B[1;36;44m";
    std::cout << "/***************************************************/" << std::endl; 
    std::cout << "\x1B[m";
    std::cout << "\x1B[31;1m Universidad Catolica San Pablo \x1B[m" << std::endl; 
    std::cout << "\x1B[33;1m Escuela Profesional de Ciencia de la Computacion \x1B[m" << std::endl; 
    std::cout << "\x1B[37;1m Curso de C++ Basico / Intermedio \x1B[m" << std::endl; 
    std::cout << "\x1B[38;5;46m Prof. D.Sc. Manuel Eduardo Loaiza Fernandez \x1B[m" << std::endl; 
    std::cout << "\x1B[3;38;5;160m Arequipa 2025 - Summer \x1B[m" << std::endl; 
    std::cout << "\x1B[5;36;44m";
    std::cout << "/***************************************************/" << std::endl;
    std::cout << "\x1B[m";
    std::cout << "\n !! Welcome to 2025 - Summer !! \n\n";

    n++;  // Incrementar n
}  

void menu() {
    std::cout << "Par number - Draw cover\nImpar number - Increment to draw\n\nEnter a number: ";
}

int main() {
    menu();
    int option;
    std::cin >> option;

    while (option <= 10) {
        if (option % 2 == 0) {
            drawCover(option);
            std::cout << "New value of option: " << option << "\n\n";
        } else {
            std::cout << "Option is " << option << ", incrementing by 1 to draw cover.\n";
            option++;  // Incrementa para hacerlo par
        }
    }

    std::cout << "Option is not par, closing program.\n";
    return 0;    
}


	
	
	
	
	






























