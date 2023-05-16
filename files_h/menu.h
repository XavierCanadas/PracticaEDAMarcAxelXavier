#include "../global.h"
#include "usuari.h"

#define MENU_ERROR_SELECT  -1

// Opcions del menú
#define NOU_USUARI 1
#define LLISTA_USUARIS 2
#define ESCOLLIR_USUARI 3
#define MOSTRAR_OPCIONS 4
#define SORTIR 5

// Opcions escollir usuari
#define ENVIAR_SOLICITUD 10
#define GESTIONAR_SOLICITUTS 11
#define FER_PUBLICACIO 12
#define VEURE_PUBLICACIONS 13

// Funcions:
int bucleMenu();
void showMenuOptions();

//void printUsers(LlistaUsers* llista);
void showEscollirUsuaruMenu();
int bucleEscollirUsuari();


