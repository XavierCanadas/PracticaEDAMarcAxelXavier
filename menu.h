#include "global.h"


#define MENU_ERROR_SELECT  -1

// Opcions del menú
#define NOU_USUARI 1
#define LLISTA_USUARIS 2
#define ESCOLLIR_USUARI 3
#define MOSTRAR_OPCIONS 4
#define SORTIR 5

// Funcions:
int bucleMenu();
void showMenuOptions();
int entradaInt();
void flush_input();


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