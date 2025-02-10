// Hello World program 
// ANSI Codes
// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797

#include <iostream>
#include <string>

#ifdef _WIN32
    //#include <windows.h>
    #define CLEAR_COMMAND "cls"
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    #include <unistd.h>
    #include <termios.h>
    #define CLEAR_COMMAND "clear"
#endif
  
void drawCover(std::string university = "Empty", std::string carrer = "Empty", std::string subject = "Empty", std::string name ="Empty") {
	
	std::system(CLEAR_COMMAND);            // Comando para borrar todo el contenido de la pantalla
    std::cout << "\x1B[H";          // Codigo para colocar el cursor en el canto superior izquierdo

    std::cout << "\x1B[1;36;44m";         // Mostrar el siguiente texto en modo de letra italico "[3;" y color azul "[ ;34m"	
	std::cout << "/***************************************************/" << std::endl; 
	std::cout << "\x1B[m";             // Resetear color a valor por defecto
	std::cout << "\x1B[31;1m" << university << "\x1B[m" << std::endl; 
	std::cout << "\x1B[33;1m" << carrer << "\x1B[m" << std::endl; 
	std::cout << "\x1B[37;1m" << subject << "\x1B[m" << std::endl; 
	std::cout << "\x1B[38;5;46m" << name << "\x1B[m" << std::endl; 
	std::cout << "\x1B[3;38;5;160m Arequipa 2025 - Summer \x1B[m" << std::endl; 
	std::cout << "\x1B[5;36;44m";         // Mostrar el siguiente texto en modo de letra italico "[3;" y color azul "[ ;34m"	
	std::cout << "/***************************************************/" << std::endl;
	std::cout << "\x1B[m";             // Resetear color a valor por defecto 
	std::cout << "\n !! Welcome to 2025 - Summer !! \n\n";
}

void menu() {
	std::cout << "1-Draw cover\n2-Modify cover\n3-Close\n\nChose an option: ";
}

void modifyCover() {
	
	std::cin.ignore(); // Elimina el '\n' pendiente por el cin
	
    std::cout << "Enter the new information for your cover" << std::endl;

    std::string university;
    std::string career;
    std::string subject;
    std::string name;

    std::cout << "University: ";
    std::getline(std::cin, university); 

    std::cout << "Career: ";
    std::getline(std::cin, career);  // Cambiado a std::getline para aceptar espacios

    std::cout << "Subject: ";
    std::getline(std::cin, subject);  

    std::cout << "Name: ";
    std::getline(std::cin, name);  

    drawCover(university, career, subject, name);
}


int main() {   

    menu();
	int option;
	std::cin >> option; // Aqui posible problema si no se ignora el salto de linea que contiene el cin

	while (option != 3) {
		if (option == 1) {
			drawCover();
		    menu();
	        std::cin >> option;
		}
	    else if (option == 2) {
		    modifyCover();
		    menu();
	        std::cin >> option;
		    
		}
	}
	
	return 0;
}



























