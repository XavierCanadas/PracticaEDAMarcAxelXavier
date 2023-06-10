#include "../files_h/usuari.h"
#include "time.h"

// Aquesta funció crea espai per un usuari i totes les variables a 0.
extern void inicializarCola(ColaSolicitudes** cola);
Usuari* initUsuari() {
    Usuari* usuari = (Usuari*) calloc(1, sizeof(Usuari));

    for (int i = 0; i < 5; ++i) {
        memset(usuari->gustos[i], 0, sizeof(usuari->gustos[i]));
    }


    // Crea espai per deu amics
    usuari->amics = (TaulaHash*) calloc(1, sizeof(TaulaHash));
    initTaulaHash(  usuari->amics, 10);

    usuari->publicacions = (Publicacio*) calloc(1, sizeof(Publicacio));
    inicializarCola(&usuari->solicitudsAmistat);
    return usuari;
}
void seleccionarGustos(Usuari* usuari) {
    // Lista de gustos en catalán
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

    // Mostrar la lista de gustos
    for (int i = 0; i < numGustos; i++) {
        printf("%d. %s\n", i + 1, gustos[i]);
    }

    // Solicitar al usuario que seleccione sus gustos
    for (int i = 0; i < 5; i++) {
        printf("Selecciona el gust numero %d: ", i + 1);
        int seleccion;
        scanf("%d", &seleccion);

        // Validar la selección del usuario
        if (seleccion >= 1 && seleccion <= numGustos) {
            strcpy(usuari->gustos[i], gustos[seleccion - 1]);
        } else {
            printf("Seleccio invalida. Intenta-ho de nou.\n");
            i--;
        }
    }
}

/// Creació i guardar un usuari
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

