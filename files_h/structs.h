//
// Created by axeld on 25/04/2023.
//
#include "../global.h"

#ifndef UNTITLED2_STRUCTS_H
#define UNTITLED2_STRUCTS_H

#endif //UNTITLED2_STRUCTS_H
//definició per les publicacions
#define MAX_CARACTERS 120

typedef struct Usuari Usuari;

typedef struct TaulaHash TaulaHash;
typedef struct ElementTaulaHash ElementTaulaHash;

typedef struct NodoSolicitud NodoSolicitud;
typedef struct ColaSolicitudes ColaSolicitudes;

typedef struct Publicacio Publicacio;
typedef struct ArrayPublciacions ArrayPublciacions;

typedef struct Tendencia Tendencia;
typedef struct ArrayTendencies ArrayTendencies;

/**
 * Estructura que defineix un usuari
 */
struct Usuari{
    char nomUsuari[MAX_STRING];
    char nom[MAX_STRING];
    int edat;
    char correu[MAX_STRING];
    char ciutat[MAX_STRING];
    char gustos[5][MAX_STRING];
    TaulaHash* amics;
    ColaSolicitudes* solicitudsAmistat;
    ArrayPublciacions* arrayPublciacions;
    int nombrePublicacions;
};


/**
 * Estructura d'un element de la taula hash per a guadar els usuaris
 */
struct ElementTaulaHash{
    char clau[MAX_STRING]; // És el nom d'usuari.
    Usuari* valor;
};
/**
 * Estructura per la taula hash per a guadar els usuaris
 */
struct TaulaHash {
    int size;
    int count;
    ElementTaulaHash* elements;
};



/**
 * Estructura d'un node de la cua per solicituds d'amistat
 */
struct NodoSolicitud {
    char remitente[MAX_STRING];
    char destinatario[MAX_STRING];
    struct NodoSolicitud* siguiente;
};
/**
 * Estructura cua per solicituds d'amistat
 */
struct ColaSolicitudes{
    NodoSolicitud* frente;
    NodoSolicitud* final;
};

/**
 * Estructura d'una Publicació
 */
struct Publicacio{
    char contingut[MAX_CARACTERS];
    char data[MAX_STRING];
    int likes;
    char nomUsuari[MAX_STRING];
} ;
/**
 * Estructura de l'array de publicacions
 */
struct ArrayPublciacions{
    Publicacio** publicacions;
    int mida;
    int nombrePublicacions;
};

/**
 * Estructura d'una Tendència
 */
struct Tendencia{
    char contingut[MAX_STRING];
    int popularitat;
};

/**
 * Estructura de l'array de tendències
 */
struct ArrayTendencies{
    Tendencia** tendencies;
    int mida;
    int nombreTendencies;
};


