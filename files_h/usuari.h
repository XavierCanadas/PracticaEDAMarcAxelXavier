//
// Created by Xavi Cañadas on 14/5/23.
//

// Includes
#include "../files_h/taulaHash.h"

#ifndef UNTITLED2_USUARI_H
#define UNTITLED2_USUARI_H

#endif //UNTITLED2_USUARI_H


// Funcions
Usuari* initUsuari();
Usuari* nouUsuari();
void imprimirUsuaris(TaulaHash* taulaHash);
void initLlistaAmics(Usuari* usuari);
Usuari* buscarUsuari(TaulaHash* taulaHash, char* nomUsuari);
// Funció per realitzar una publicació
void realitzarPublicacio(Usuari* usuari);

// Funció per mostrar les publicacions d'un usuari
void mostrarPublicacions(TaulaHash* taula);

// Funció per donar "m'agrada" a una publicació
void donarMAgrada(Usuari* usuari);
