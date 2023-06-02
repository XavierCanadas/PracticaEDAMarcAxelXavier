//
// Created by USUARI on 02/06/2023.
//
#include "../files_h/structs.h"
#ifndef UNTITLED2_COLA_H
#define UNTITLED2_COLA_H

#endif //UNTITLED2_COLA_H
///Estructures cua per solicituds d'amistat
typedef struct Nodo {
    char remitent[MAX_STRING];
    char destinatari[MAX_STRING];
    struct Nodo* siguiente;
} NodoSolicitud;

typedef struct {
    NodoSolicitud* Top;
    NodoSolicitud* Bottom;
} ColaSolicitudes;