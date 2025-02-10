#include <iostream>

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    #include <unistd.h>
    #include <termios.h>
    #define CLEAR_COMMAND "clear"
#endif

void drawCover(int* counter, const char* university, const char* carrer, const char* course, const char* name) {
    //std::system(CLEAR_COMMAND); 
    std::cout << "\x1B[H";  

    std::cout << "\x1B[1;36;44m";	
    std::cout << "/***************************************************/" << std::endl; 
    std::cout << "\x1B[m";  
    std::cout << "\x1B[31;1m " << university << " \x1B[m" << std::endl; 
    std::cout << "\x1B[33;1m " << carrer << " \x1B[m" << std::endl; 
    std::cout << "\x1B[37;1m " << course << " \x1B[m" << std::endl; 
    std::cout << "\x1B[38;5;46m " << name << " \x1B[m" << std::endl; 
    std::cout << "\x1B[3;38;5;160m Arequipa 2025 - Summer \x1B[m" << std::endl; 
    std::cout << "\x1B[5;36;44m";	
    std::cout << "/***************************************************/" << std::endl;
    std::cout << "\x1B[m";  
    std::cout << "\n !! Welcome to 2025 - Summer !! \n\n";
    
    (*counter)++; // Incrementa el contador
}  

int main() {
    const char* university = "Universidad Catolica San Pablo";
    const char* carrer = "Escuela Profesional de Ciencia de la Computacion";
    const char* course = "Curso de C++ Basico / Intermedio";
    const char* name = "Alberto Fabricio Lescano Taype";

    int count = 0;

    while (count < 3) {  // Dibujará la carátula 3 veces
        drawCover(&count, university, carrer, course, name);
        std::cout << "Carátula dibujada " << count << " veces\n";
    }

    return 0;
}




	
	
	
	
	






























