//
// Created by Xavi Cañadas on 15/5/23.
//
#include "../files_h/taulaHash.h"

/// Taula Hash:

/* Explicació funció hash:
 *
 * La funció hash rep una clau del tipus String i una taula hash, al principi truca a la funció
 * charToIntASCII() per convertir la clau en un nombre. Després aplica el mòdul al nombre de la clau
 * i comproba si amb l'índex que ha donat, a la taula aquest índex està ocupat o lliure. Si està lliure
 * o està ocupat per la mateixa clau retorna l'índex trobat, sinó torna a aplicar el mòdul al nombre,
 * però aquesta vegada sumant-li +1 i torna a mirar la condició.
 * (La comprobació de col·lisions es fa a la funció guardarUsuari())
 */

int hashing(char* clau, TaulaHash* taulaHash) {
    int index, i = 0;
    int clauASCII = charToIntASCII(clau);
    char clauAux[MAX_STRING];


    do {
        // S'aplica el mòdul al nombre clauASCII % mida de la taula
        index = (clauASCII + i) % taulaHash->size;
        // Agafa la clau guardada a la posició de l'índex trobat per després comparar.
        strcpy(clauAux, taulaHash->elements[index].clau);

        // Es complirà quan s'ha recorregut tota la taula
        if (i == taulaHash->size) {
            return ERROR_CALCULAR_INDEX;
        }

        i++;
    } while (strcmp("", clauAux) != 0 && strcmp(clau, clauAux) != 0);

    return index;
}

int charToIntASCII(char* string) {
    int resultat = 0;
    for (int i = 0; i < strlen(string); ++i) {
        int valorASCII = (int) string[i];
        resultat += valorASCII;
    }
    return resultat;
}

void initTaulaHash(TaulaHash* taulaHash, int size) {
    ElementTaulaHash* llistaElements = (ElementTaulaHash*) malloc(sizeof(ElementTaulaHash)*size);
    taulaHash->elements = llistaElements;
    taulaHash->size = size;
    taulaHash->count = 0;

    for (int i = 0; i < taulaHash->size; ++i) {
        memset(taulaHash->elements[i].clau, 0, sizeof(taulaHash->elements->clau));
        taulaHash->elements[i].valor = NULL;
    }
}

int guardarUsuari(Usuari* usuari, TaulaHash* taulaHash,  int *indexGuardat) {
    int index = hashing(usuari->nomUsuari, taulaHash);

    // Si hi ha un error al calcular l'índex o si el nou usuari que es vol guardar ja està a la taula es retirna ERROR.
    if (index == ERROR_CALCULAR_INDEX || (strcmp(usuari->nom, taulaHash->elements[index].clau)) == 0)
        return ERROR_GUARDAR_USUARU;


    // S'assigna la clau i el valor a la posició de l'índex retornat per hashing()
    strcpy(taulaHash->elements[index].clau, usuari->nomUsuari);
    taulaHash->elements[index].valor = usuari;

    taulaHash->count++;

    *indexGuardat = index;

    return SUCCESS;
}

int taulaHashPlena(TaulaHash* taulaHash) {
    // S'afegeix espai per 10 usuaris més
    taulaHash->size += 10;

    // Si no es fa amb una variable auxiliar surt un warning.

    ElementTaulaHash* aux;
    aux = (ElementTaulaHash *) realloc(taulaHash->elements, taulaHash->size * sizeof(ElementTaulaHash));

    if (taulaHash->elements == NULL)
        return ERROR_AMPLIAR_TAULA;

    taulaHash->elements = aux;

    // Tornar a calcular tots els nous índex. El bucle és fins a size/2 perquè els elements estaran
    // a la primera meitat de l'actual taula.

    /*
     * Aquest for itera per tota la taula des de l'últim element fins al primer. Primer assigna NULL als 10 últims
     * elements, que són els que s'han creat amb el realloc anterior. A continuació calcula el nou índex pels elements que
     * hi havia guardats a la taula.
     */
    for (int i = taulaHash->size - 1; i >= 0; i--) {
        if (i >= taulaHash->size - 10) {
            taulaHash->elements[i].valor = NULL;
            // Posa que tots els caràcters de la clau siguin '0'.
            memset(taulaHash->elements[i].clau, 0, sizeof(taulaHash->elements[i].clau));
        } else {
            int indexGuardat;
            guardarUsuari(taulaHash->elements[i].valor, taulaHash, &indexGuardat);

            if (indexGuardat != i) {
                taulaHash->elements[i].valor = NULL;
                // Posa que tots els caràcters de la clau siguin '0'.
                memset(taulaHash->elements[i].clau, 0, sizeof(taulaHash->elements[i].clau));
            }
        }
    }

    return SUCCESS;
}

void eliminarUsuari(TaulaHash* taulaHash, int index) {
    // Eliminar l'usuari
    free(taulaHash->elements[index].valor);
    memset(taulaHash->elements[index].clau, 0, sizeof(taulaHash->elements->clau));
}

void eliminarTaulaHash(TaulaHash* taulaHash) {
    // primer iterar per cada element de la taula i eliminar-lo.
    for (int i = 0; i < taulaHash->size; ++i) {
        eliminarUsuari(taulaHash, i);
    }
    // elimina l'array d'usuaris
    free(taulaHash->elements);
    // eliminar la taula
    free(taulaHash);
}