//
// Created by Xavi Cañadas on 14/5/23.
//

// Includes
#include "taulaHash.h"

#ifndef UNTITLED2_USUARI_H
#define UNTITLED2_USUARI_H

#endif //UNTITLED2_USUARI_H


// Funcions
Usuari* nouUsuari();
void imprimirUsuaris(TaulaHash* taulaHash);
Usuari* buscarUsuari(TaulaHash* taulaHash, char* nomUsuari);


/// Estructura per la taula hash per guadar els usuaris
typedef struct {
    char clau[MAX_STRING]; // És el nom d'usuari.
    Usuari* valor;
} ElementTaulaHash;

typedef struct {
    int size;
    int count;
    ElementTaulaHash* elements;
} TaulaHash;