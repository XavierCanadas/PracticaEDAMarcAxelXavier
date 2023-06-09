//Includes
#include "global.h"
#include "files_h/menu.h"


//El Main nomes inicialitza el codi, en concret el bucle del menu.
int main() {
    //Borra tots els missatges a la terminal fins el moment
    printf("\033[2J");

    //Inicia el programa
    bucleMenu();
}

