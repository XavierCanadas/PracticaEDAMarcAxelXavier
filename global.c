//
// Created by Xavi Cañadas on 5/5/23.
//
#include "global.h"


// Aquesta funció serveix perquè l'usuari introdueixi un enter, el paràmetre és per imprimir un missatge per l'usuari.
// retorna
int entradaInt(char missatge[]) {
    int nombreEnter;
    printf("%s", missatge);
    if (scanf("%d", &nombreEnter) == ERROR_ENTRADA_DADES) {
        nombreEnter = ERROR_ENTRADA_DADES;
    }
    flush_input();
    return nombreEnter;
}

int entradaString(char missatge[], char entradaUsuari[]);

// Aquesta funció estava a la pràctica d'EDA-I, si no s'executa al final de trucar a "scanf" poden sortir bugs
// que facin que hi hagi bucles infinits en el menú.
void flush_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}