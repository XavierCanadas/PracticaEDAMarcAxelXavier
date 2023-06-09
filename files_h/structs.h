//Includes
#include "../global.h"

#ifndef UNTITLED2_STRUCTS_H
#define UNTITLED2_STRUCTS_H
#endif //UNTITLED2_STRUCTS_H

//definicions per les publicacions
#define MAX_PUBLICACIONS 100
#define MAX_CARACTERS 120


//Struct de la publicacio
typedef struct {
    char data[MAX_STRING];
    char contingut[MAX_CARACTERS];
    int mAgrada;
} Publicacio;

typedef struct TaulaHash TaulaHash;

//Struct del Usuari
typedef struct {
    char nomUsuari[MAX_STRING];
    char nom[MAX_STRING];
    int edat;
    char correu[MAX_STRING];
    char ciutat[MAX_STRING];
    char gustos[5][MAX_STRING];
    TaulaHash* amics;
    TaulaHash* solicitudsAmistat;
    Publicacio publicacions[MAX_PUBLICACIONS];
    int numPublicacions;
} Usuari;


// Estructura per la taula hash per guadar els usuaris
typedef struct {
    char clau[MAX_STRING]; // És el nom d'usuari.
    Usuari* valor;
} ElementTaulaHash;

struct TaulaHash {
    int size;
    int count;
    ElementTaulaHash* elements;
};


//Estructures cua per solicituds d'amistat
typedef struct Nodo {
    char remitente[MAX_STRING];
    char destinatario[MAX_STRING];
    struct Nodo* siguiente;
} NodoSolicitud;

typedef struct {
    NodoSolicitud* frente;
    NodoSolicitud* final;
} ColaSolicitudes;
