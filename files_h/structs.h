//
// Created by axeld on 25/04/2023.
//
#include "../global.h"

#ifndef UNTITLED2_STRUCTS_H
#define UNTITLED2_STRUCTS_H

#endif //UNTITLED2_STRUCTS_H
typedef struct TaulaHash TaulaHash;
typedef struct usuari{
    char nomUsuari[MAX_STRING];
    char nom[MAX_STRING];
    int edat;
    char correu[MAX_STRING];
    char ciutat[MAX_STRING];
    // Això ho canviaria i ho faria amb una enumeració
    char gustos[5][MAX_STRING];
    TaulaHash* amics;
    TaulaHash* solicitudsAmistat;
} Usuari;


/*
typedef struct {
    Usuari *llista;
    int num_users;
}LlistaUsers;
 */

/// Estructura per la taula hash per guadar els usuaris
typedef struct {
    char clau[MAX_STRING]; // És el nom d'usuari.
    Usuari* valor;
} ElementTaulaHash;

struct TaulaHash{
    int size;
    int count;
    ElementTaulaHash* elements;
};
