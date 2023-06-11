#include "../files_h/usuari.h"
#include "time.h"

// s'agafen funcions de cola.h sense incluir tot l'arxiu perquè produia errors inesperats.
extern void inicializarCola(ColaSolicitudes** cola);
extern ArrayPublciacions* initArrayPublicacions(int mida);

/**
 * Es reserva espai a memòria per un usuari i s'inicialitza totes les seves variables a NULL o 0 (amb calloc).
 * @return: es retorna l'usuari inicialitzat
 */
Usuari* initUsuari() {
    Usuari* usuari = (Usuari*) calloc(1, sizeof(Usuari));

    for (int i = 0; i < 5; ++i) {
        memset(usuari->gustos[i], 0, sizeof(usuari->gustos[i]));
    }

    // Crea espai per deu amics
    usuari->amics = (TaulaHash*) calloc(1, sizeof(TaulaHash));
    initTaulaHash(  usuari->amics, 10);

    usuari->arrayPublciacions = initArrayPublicacions(10);

    inicializarCola(&usuari->solicitudsAmistat);
    return usuari;
}
/**
 * Aquesta funció s'encarrega de demanar a l'usuari que esculli els seus gustos d'una llista predeterminada.
 * @param usuari
 */
void seleccionarGustos(Usuari* usuari) {
    // Lista de gustos
    const char* gustos[] = {
            "Cuina",
            "Esport",
            "Musica",
            "Art",
            "Natura",
            "Cinema",
            "Lectura",
            "Viatges",
            "Historia",
            "Cuina",
            "Moda"
    };

    const int numGustos = sizeof(gustos) / sizeof(gustos[0]);

    printf("Selecciona els %d gustos que millor et defineixin:\n", 5);

    // Mostra la llista de gustos
    for (int i = 0; i < numGustos; i++) {
        printf("%d. %s\n", i + 1, gustos[i]);
    }

    // Solicita l'usuari que seleccioni els seus gustos
    for (int i = 0; i < 5; i++) {
        printf("Selecciona el gust numero %d: ", i + 1);
        int seleccion = entradaInt(" ");

        // Valida la selecció de l'usuari
        if (seleccion >= 1 && seleccion <= numGustos) {
            strcpy(usuari->gustos[i], gustos[seleccion - 1]);
        } else {
            printf("Seleccio invalida. Intenta-ho de nou.\n");
            i--;
        }
    }
}

/// Creació i guardar un usuari
/**
 * La funció inicialitza un Usuari i demana a l'usuari que introdueixi les dades.
 * @return
 */
Usuari* nouUsuari() {
    Usuari *user = initUsuari();

    // El nom d'usuari es convertirà a tot minuscules.
    entradaString("Introdueixi el seu nom: ", user->nom, "name");
    entradaString("Introdueixi el seu nom d'usuari: ", user->nomUsuari, "none");
    entradaString("Introdueixi la seva ciutat: ", user->ciutat, "city");
    entradaString("Introdueixi el seu correu: ", user->correu, "mail");
    user->edat = entradaInt("Introdueixi la seva edat: ");
    seleccionarGustos(user);

    // Es converteix el nom d'usuari a minúscules
    for (int i = 0; i < strlen(user->nomUsuari); ++i) {
        if (isalpha(user->nomUsuari[i])) // Verifica si és una lletra.
            user->nomUsuari[i] = (char) tolower(user->nomUsuari[i]);
    }

    return user;
}

void imprimirUsuaris(TaulaHash* taulaHash) {
    // Recorrer tota la taula i imprimir
    int k=0, count = 0;
    for (int i = 0; i < taulaHash->size; ++i) {
        if (taulaHash->elements[i].clau[0] != '\0') {
            count++;
            printf("%d. Nom usuari: %s\n",count, taulaHash->elements[i].valor->nomUsuari);
            k++;
        }
    }
    if(k==0) printf("No hi ha usuaris per imprimir\n");
}

// Funció buscar usuari: s'ha de trucar a la funció hashing
Usuari* buscarUsuari(TaulaHash* taulaHash, char* nomUsuari) {
    int idx = hashing(nomUsuari, taulaHash, false);
    if (idx==ERROR_CALCULAR_INDEX) return NULL;
    return taulaHash->elements[idx].valor;
}

