//
// Created by Xavi Cañadas on 15/5/23.
//

#ifndef UNTITLED2_TAULAHASH_H
#define UNTITLED2_TAULAHASH_H

#endif //UNTITLED2_TAULAHASH_H

/// Llibreries
#include "structs.h"

/// Errors
#define ERROR_CALCULAR_INDEX -10
#define ERROR_GUARDAR_USUARU -10
#define ERROR_AMPLIAR_TAULA -20


/// Funcions
int hashing(char* clau, TaulaHash* taulaHash);
int charToIntASCII(char* string);
int guardarUsuari(Usuari* usuari, TaulaHash* taulaHash, int *indexGuardat);
int taulaHashPlena(TaulaHash* taulaHash);
void initTaulaHash(TaulaHash* taulaHash, int size);
void eliminarUsuari(TaulaHash* taulaHash, int index);
void eliminarTaulaHash(TaulaHash* taulaHash);