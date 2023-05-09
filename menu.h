#include "global.h"


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
Usuari* nouUsuari();
int entradaNouUsuari();
void printUsers(LlistaUsers* llista)
void showEscollirUsuaruMenu();
int bucleEscollirUsuari();



/*
 * Insertar un nuevo usuario
Listar todos los usuarios existentes
Operar como un usuario específico (Ya que nuestra aplicación no tiene sistema de login, vamos a usar un submenú que nos permita actuar como un usuario determinado)
Enviar solicitudes de amistad
Gestionar las solicitudes pendientes
Realizar una publicación
Listar las publicaciones del usuario seleccionado
volver al menú principal.
Salir (Terminar ejecución)

 */