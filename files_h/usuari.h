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
void imprimirUnUsuari(Usuari* usuari);
void initLlistaAmics(Usuari* usuari);
Usuari* buscarUsuari(TaulaHash* taulaHash, char* nomUsuari);

