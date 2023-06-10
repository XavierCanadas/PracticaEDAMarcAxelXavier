//
// Created by axeld on 25/04/2023.
//
#include "../global.h"

#ifndef UNTITLED2_STRUCTS_H
#define UNTITLED2_STRUCTS_H

#endif //UNTITLED2_STRUCTS_H
//definicions per les publicacions
#define MAX_PUBLICACIONS 100
#define MAX_CARACTERS 120

typedef struct {
    char contingut[MAX_CARACTERS];
    char data[MAX_STRING];
    int likes;
    char* usuarisMagrada[MAX_STRING];
} Publicacio;

typedef struct {
    Publicacio** publicacions;
    int mida;
    int nombrePublicacions;
}ArrayPublciacions;

typedef struct TaulaHash TaulaHash;
typedef struct ColaSolicitudes ColaSolicitudes;

typedef struct {
    char nomUsuari[MAX_STRING];
    char nom[MAX_STRING];
    int edat;
    char correu[MAX_STRING];
    char ciutat[MAX_STRING];
    char gustos[5][MAX_STRING];
    TaulaHash* amics;
    ColaSolicitudes* solicitudsAmistat;
    Publicacio* publicacions;
    int nombrePublicacions;
} Usuari;


/// Estructura per la taula hash per guadar els usuaris
typedef struct {
    char clau[MAX_STRING]; // És el nom d'usuari.
    Usuari* valor;
} ElementTaulaHash;

struct TaulaHash {
    int size;
    int count;
    ElementTaulaHash* elements;
};


///Estructures cua per solicituds d'amistat
typedef struct Nodo {
    char remitente[MAX_STRING];
    char destinatario[MAX_STRING];
    struct Nodo* siguiente;
} NodoSolicitud;

struct ColaSolicitudes{
    NodoSolicitud* frente;
    NodoSolicitud* final;
} ;

typedef struct Tendencia{
    char contingut[MAX_STRING];
    int popularitat;
}Tendencia;


