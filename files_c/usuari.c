//
// Created by Xavi Cañadas on 14/5/23.
//
#include "../files_h/usuari.h"


/// Creació i guardar un usuari
Usuari* nouUsuari() {
    Usuari *user = (Usuari *) malloc(sizeof(Usuari));

    entradaString("Introdueixi el seu nom: ", user->nom);
    entradaString("Introdueixi el seu nom d'usuari: ", user->nomUsuari);
    entradaString("Introdueixi la seva ciutat: ", user->ciutat);
    entradaString("Introdueixi el seu correu: ", user->correu);
    user->edat = entradaInt("Introdueixi la seva edat: ");

    for (int i = 0; i < 1; i++) {
        entradaString("Introdueixi un gust: ", user->gustos[i]);
        if (strcmp(user->gustos[i],"\n") == 0) break;
    }
    user->amics = (Usuari *) malloc(10*sizeof(Usuari));
    return user;
}

void imprimirUsuaris(TaulaHash* taulaHash) {
    // Recorrer tota la taula i imprimir
    int k=0;
    for (int i = 0; i < taulaHash->size; ++i) {
        if (taulaHash->elements[i].valor != NULL) {
            printf("Nom usuari %d %s\n", i, taulaHash->elements[i].valor->nomUsuari);
            k++;
        }
    }
    if(k==0) printf("No hi ha usuaris per imprimir\n");
}

// Funció buscar usuari: s'ha de trucar a la funció hashing
Usuari* buscarUsuari(TaulaHash* taulaHash, char* nomUsuari) {
    int idx = hashing(nomUsuari, taulaHash);
    if (idx==ERROR_CALCULAR_INDEX) return NULL;
    return taulaHash->elements[idx].valor;
}