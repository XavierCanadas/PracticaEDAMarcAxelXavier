//
// Created by Xavi Cañadas on 14/5/23.
//
#include "../files_h/usuari.h"

// Aquesta funció crea espai per un usuari i totes les variables a 0.
Usuari* initUsuari() {
    Usuari* usuari = (Usuari*) malloc(sizeof(Usuari));

    memset(usuari->nom, 0, sizeof(usuari->nom));
    memset(usuari->nomUsuari, 0, sizeof(usuari->nomUsuari));
    usuari->edat = 0;
    memset(usuari->correu, 0, sizeof(usuari->correu));
    memset(usuari->ciutat, 0, sizeof(usuari->ciutat));


    // Crea espai per deu amics
    usuari->amics = (TaulaHash*) malloc(sizeof(TaulaHash));
    initTaulaHash(  usuari->amics, 10);

    return usuari;
}
void seleccionarGustos(Usuari* usuari) {
    // Lista de gustos en catalán
    const char* gustos[] = {
            "Cuina",
            "Esport",
            "Música",
            "Art",
            "Natura",
            "Cinema",
            "Lectura",
            "Viatges",
            "Història",
            "Cuina",
            "Moda"
    };

    const int numGustos = sizeof(gustos) / sizeof(gustos[0]);

    printf("Selecciona els %d gustos que millor et defineixin:\n", 5);

    // Mostrar la lista de gustos
    for (int i = 0; i < numGustos; i++) {
        printf("%d. %s\n", i + 1, gustos[i]);
    }

    // Solicitar al usuario que seleccione sus gustos
    for (int i = 0; i < 5; i++) {
        printf("Selecciona el gust número %d: ", i + 1);
        int seleccion;
        scanf("%d", &seleccion);

        // Validar la selección del usuario
        if (seleccion >= 1 && seleccion <= numGustos) {
            strcpy(usuari->gustos[i], gustos[seleccion - 1]);
        } else {
            printf("Selecció invàlida. Intenta-ho de nou.\n");
            i--;
        }
    }
}

/// Creació i guardar un usuari
Usuari* nouUsuari() {
    Usuari *user = initUsuari();

    // El nom d'usuari es convertirà a tot minuscules.

    entradaString("Introdueixi el seu nom: ", user->nom, "name");
    entradaString("Introdueixi el seu nom d'usuari: ", user->nomUsuari, "user");
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
        if (taulaHash->elements[i].valor != NULL) {
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