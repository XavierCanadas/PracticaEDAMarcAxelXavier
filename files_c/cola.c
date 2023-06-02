//
// Created by USUARI on 02/06/2023.
//
#include "../files_h/taulaHash.h"

/**
 * Inicialitza la cua de sol·licituds.
 */
void inicializarCola(ColaSolicitudes* cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

/**
 * Comprova si la cua de sol·licituds està buida.
 * Retorna true si la cua està buida, false en cas contrari.
 */
bool colaVacia(ColaSolicitudes* cola) {
    return cola->frente == NULL;
}

/**
 * Afegeix una nova sol·licitud de amistat a la cua.
 */
void encolar(ColaSolicitudes* cola, const char* remitente, const char* destinatario) {
    NodoSolicitud* nuevoNodo = (NodoSolicitud*)malloc(sizeof(NodoSolicitud));
    strcpy(nuevoNodo->remitente, remitente);
    strcpy(nuevoNodo->destinatario, destinatario);
    nuevoNodo->siguiente = NULL;

    if (colaVacia(cola)) {
        cola->frente = nuevoNodo;
        cola->final = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
        cola->final = nuevoNodo;
    }

    printf("Sol·licitud d'amistat enviada a %s.\n", destinatario);
}

/**
 * Elimina la sol·licitud de amistat del davant de la cua.
 */
void desencolar(ColaSolicitudes* cola) {
    if (colaVacia(cola)) {
        printf("La cua de sol·licituds està buida.\n");
        return;
    }

    NodoSolicitud* nodoEliminar = cola->frente;
    printf("Sol·licitud d'amistat de %s acceptada.\n", nodoEliminar->remitente);

    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoEliminar);
}

/**
 * Rebutja la sol·licitud de amistat del davant de la cua.
 */
void rechazarSolicitud(ColaSolicitudes* cola) {
    if (colaVacia(cola)) {
        printf("La cua de sol·licituds està buida.\n");
        return;
    }

    NodoSolicitud* nodoEliminar = cola->frente;
    printf("Sol·licitud d'amistat de %s rebutjada.\n", nodoEliminar->remitente);

    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoEliminar);
}

/**
 * Accepta la sol·licitud de amistat del davant de la cua.
 * Afegeix l'amistat a la llista d'amics de l'usuari.
 */
void acceptarSolicitud(ColaSolicitudes* cola, Usuari* usuari) {
    if (colaVacia(cola)) {
        printf("No hay solicitudes de amistad pendientes.\n");
        return;
    }
    NodoSolicitud* nodoAceptar = cola->frente;
    printf("Aceptando solicitud de amistad de %s...\n", nodoAceptar->remitente);

    // Agregar remitente como amigo
    int indexAmic;
    int resultado = guardarUsuari(usuari->amics, nodoAceptar->remitente, &indexAmic);
    if (resultado == SUCCESS) {
        printf("Solicitud de amistad aceptada. %s ahora es tu amigo.\n", nodoAceptar->remitente);
    } else {
        printf("Error al aceptar solicitud de amistad.\n");
    }

    desencolar(cola);
    free(nodoAceptar);
}



/**
 * Gestiona les sol·licituds d'amistat.
 * Proporciona un menú per enviar, acceptar o rebutjar sol·licituds de amistat.
 */
void gestionSolicitudesAmistad(Usuari* usuari) {
    ColaSolicitudes cola;
    inicializarCola(&cola);

    int opcion = 0;
    while (opcion != 4) {
        printf("----- GESTIÓ DE SOL·LICITUDS D'AMISTAT -----\n");
        printf("1. Enviar sol·licitud d'amistat\n");
        printf("2. Acceptar sol·licitud d'amistat\n");
        printf("3. Rebutjar sol·licitud d'amistat\n");
        printf("4. Sortir\n");
        opcion = entradaInt("\"Introdueix el número de l'opció desitjada: \"");

        switch (opcion) {
            case 1: {
                char remitente[MAX_STRING];
                char destinatario[MAX_STRING];
                entradaString("Introdueix el nom d'usuari de l'emissor: ", remitente);
                entradaString("Introdueix el nom d'usuari del destinatari: ", destinatario);
                if(strcmp(remitente,destinatario)!=0) encolar(&cola, remitente, destinatario);
                else printf("Error al enviar la sol·licitud");
                break;
            }
            case 2:
                acceptarSolicitud(&cola, usuari);
                break;
            case 3:
                rechazarSolicitud(&cola);
                break;
            case 4:
                printf("Surt del programa...\n");
                break;
            default:
                printf("Opció invàlida. Si us plau, introdueix un número vàlid.\n");
                break;
        }

        printf("---------------------------------------------\n\n");
    }
}