#include "../global.h"
#include "../files_h/cola.h"

#define MENU_ERROR_SELECT  -1

// Opcions del menú
#define NOU_USUARI 1
#define LLISTA_USUARIS 2
#define ESCOLLIR_USUARI 3
#define MOSTRAR_OPCIONS 4
#define SORTIR 5

// Opcions escollir usuari
#define GESTIONAR_SOLICITUTS 11
#define FER_PUBLICACIO 12
#define VEURE_PUBLICACIONS 13
#define EDITAR_USUARI 14
#define ELIMINAR_USUARI 15

// Funcions:
int bucleMenu();
void showMenuOptions();

//void printUsers(LlistaUsers* llista);
void showEscollirUsuaruMenu();
int bucleEscollirUsuari(TaulaHash* taula);


