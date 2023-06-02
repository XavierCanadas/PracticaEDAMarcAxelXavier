//
// Created by USUARI on 02/06/2023.
//
/*
#include "../files_h/cola.h"

void inicializarCola(ColaSolicitudes* cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

bool colaVacia(ColaSolicitudes* cola) {
    return cola->frente == NULL;
}

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

    printf("Solicitud de amistad enviada a %s.\n", destinatario);
}

void desencolar(ColaSolicitudes* cola) {
    if (colaVacia(cola)) {
        printf("La cola de solicitudes está vacía.\n");
        return;
    }

    NodoSolicitud* nodoEliminar = cola->frente;
    printf("Solicitud de amistad de %s aceptada.\n", nodoEliminar->remitente);

    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoEliminar);
}

void rechazarSolicitud(ColaSolicitudes* cola) {
    if (colaVacia(cola)) {
        printf("La cola de solicitudes está vacía.\n");
        return;
    }

    NodoSolicitud* nodoEliminar = cola->frente;
    printf("Solicitud de amistad de %s rechazada.\n", nodoEliminar->remitente);

    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoEliminar);
}
 */