#include "../files_h/taulaHash.h"

// Taula Hash:

/**
 * La funció hash rep una clau del tipus String i una taula hash, al principi truca a la funció
  charToIntASCII() per convertir la clau en un nombre. Després aplica el mòdul al nombre de la clau
  i comproba si amb l'índex que ha donat, a la taula aquest índex està ocupat o lliure. Si està lliure
  o està ocupat per la mateixa clau retorna l'índex trobat, sinó torna a aplicar el mòdul al nombre,
  però aquesta vegada sumant-li +1 i torna a mirar la condició.
 (La comprobació de col·lisions es fa a la funció guardarUsuari())
 * @param clau
 * @param taulaHash
 * @param esNouUsuari
 * @return
 */
int hashing(char* clau, TaulaHash* taulaHash, bool esNouUsuari) {
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
        if (esNouUsuari == true && strcmp(clau, clauAux) == 0) {
            printf("Aquest usuari ja està creat!\n");
            return ERROR_CALCULAR_INDEX;
        }

        i++;
    } while (strcmp("", clauAux) != 0 && strcmp(clau, clauAux) != 0);

    return index;
}

/**
 * La funció rep una string, itera per cada caracter i va sumant tots els valors ascii i retorna el valor de la suma final.
 * @param string
 * @return
 */
int charToIntASCII(char* string) {
    int resultat = 0;
    for (int i = 0; i < strlen(string); ++i) {
        int valorASCII = (int) string[i];
        resultat += valorASCII;
    }
    return resultat;
}
/**
 * Es passa un punter de taula hash, amb memòria reservada ja, la funció asigna tots els valors a 0 i també crea espai per
 * el nombre d'elements que spha definit al paràmetre.
 * @param taulaHash
 * @param size
 */
void initTaulaHash(TaulaHash* taulaHash, int size) {
    ElementTaulaHash* llistaElements = (ElementTaulaHash*) calloc(size,sizeof(ElementTaulaHash));
    taulaHash->elements = llistaElements;
    taulaHash->size = size;
    taulaHash->count = 0;

    for (int i = 0; i < taulaHash->size; ++i) {
        memset(taulaHash->elements[i].clau, 0, sizeof(taulaHash->elements->clau));
        taulaHash->elements[i].valor = NULL;
    }
}
/**
 * La finalitat de la funció és guardar un usuari a la taula hash, per fer això primer calcula l'índex que ha de tenir
 * trucant a hashing i després el guarda a la seva posició.
 * @param usuari
 * @param nomUsuari
 * @param taulaHash
 * @param indexGuardat: s'utilitza només per poder ampliar la taula correctament a la funció taulaHashPlena().
 * @return
 */
int guardarUsuari(Usuari* usuari, char* nomUsuari, TaulaHash* taulaHash, int *indexGuardat) {
    int index = hashing(nomUsuari, taulaHash, true);

    // Si hi ha un error al calcular l'índex o si el nou usuari que es vol guardar ja està a la taula es retirna ERROR.
    if (usuari != NULL) {
        if ((strcmp(usuari->nom, taulaHash->elements[index].clau) || index == ERROR_CALCULAR_INDEX) == 0) {
            return ERROR_GUARDAR_USUARU;
        }
    }


    // S'assigna la clau i el valor a la posició de l'índex retornat per hashing()
    strcpy(taulaHash->elements[index].clau, nomUsuari);

    if (usuari != NULL)
        taulaHash->elements[index].valor = usuari;

    taulaHash->count++;

    if (indexGuardat != NULL)
        *indexGuardat = index;

    return SUCCESS;
}

/**
 * Quan la taulaHash s'emplena, aquesta funció s'encarrega de reservar més espai i tornar a asignar els nous índex a la posició
 * que li correspon a cada usuari.
 * @param taulaHash
 * @return
 */
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
            guardarUsuari(taulaHash->elements[i].valor, taulaHash->elements[i].valor->nomUsuari, taulaHash, &indexGuardat);

            if (indexGuardat != i) {
                taulaHash->elements[i].valor = NULL;
                // Posa que tots els caràcters de la clau siguin '0'.
                memset(taulaHash->elements[i].clau, 0, sizeof(taulaHash->elements[i].clau));
            }
        }
    }

    return SUCCESS;
}
// Aquestes funcions s'usen per poder lliberar de la memòria correctament els usuaris que es volen eliminar.
extern void freeArrayPublicacions(ArrayPublciacions* arrayPublciacions);
extern bool colaVacia(ColaSolicitudes* cola);
extern void desencolar(ColaSolicitudes* cola);

/**
 * La funció llibera de memòria cada component d'un usuari passat i després llibera l'usuari i així s'elimina.
 * @param taulaHash
 * @param index
 */
 extern Usuari* initUsuari();
void eliminarUsuari(TaulaHash* taulaHash, int index) {
    Usuari* usuari = taulaHash->elements[index].valor;

    // Eliminar l'usuari
    if (usuari != NULL) {
        if (usuari->arrayPublciacions != NULL)
            freeArrayPublicacions(usuari->arrayPublciacions);

        while (colaVacia(usuari->solicitudsAmistat) == false)
            desencolar(usuari->solicitudsAmistat);

        if (usuari->solicitudsAmistat != NULL)
            free(usuari->solicitudsAmistat);

        if (usuari->amics != NULL) {
            free(usuari->amics->elements);
            free(usuari->amics);

        }


        free(usuari);
        taulaHash->elements[index].valor = NULL;
        taulaHash->count--;

    }
    memset(taulaHash->elements[index].clau, 0, sizeof(taulaHash->elements->clau));
}

/**
 * La funció recorre tota la taula hash i elimina cada usuari trucant a eliminarUsuari().
 * @param taulaHash
 */
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