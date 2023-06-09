#include "../files_h/usuari.h"
#include "time.h"

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

///Funcions per les publicacions
#include <time.h>

void realitzarPublicacio(Usuari* usuari) {
    char contingut[MAX_STRING];
    printf("Introdueix el contingut de la publicacio (maxim %d caracters): ", MAX_CARACTERS);
    fflush(stdout);
    fgets(contingut, sizeof(contingut), stdin);

    // Eliminar el salto de línea al final del texto
    contingut[strcspn(contingut, "\n")] = '\0';

    // Verificar la longitud de la publicación
    if (strlen(contingut) > MAX_CARACTERS) {
        printf("El contingut de la publicacio es massa llarg.\n");
        return;
    }

    // Crear la publicación y agregarla al array de publicaciones del usuario
    Publicacio publicacio;
    strcpy(publicacio.contingut, contingut);
    publicacio.mAgrada = 0;

    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm* fecha = localtime(&t);

    // Formatear la fecha en el formato deseado (dd/mm/aaaa)
    snprintf(publicacio.data, sizeof(publicacio.data), "%02d/%02d/%d", fecha->tm_mday, fecha->tm_mon + 1, fecha->tm_year + 1900);

    if (usuari->numPublicacions >= MAX_PUBLICACIONS) {
        printf("Has arribat al limit maxim de publicacions.\n");
        return;
    }

    usuari->publicacions[usuari->numPublicacions] = publicacio;
    usuari->numPublicacions++;

    printf("Publicacio realitzada amb exit.\n");
}


void mostrarPublicacions(TaulaHash* taula) {
    char nomUsuari[MAX_STRING];
    entradaString("Introdueix el nom d'usuari per mostrar les publicacions: ", nomUsuari, "none");

    // Buscar l'usuari a partir del nom d'usuari proporcionat
    Usuari* usuari = buscarUsuari(taula, nomUsuari);
    if (usuari == NULL) {
        printf("No s'ha trobat cap usuari amb aquest nom.\n");
        return;
    }

    printf("Publicacions de l'usuari %s:\n", usuari->nomUsuari);

    for (int i = 0; i < usuari->numPublicacions; i++) {
        printf("---------------------------------------------------\n");
        printf("                Publicación %d\n", i + 1);
        printf("---------------------------------------------------\n");
        printf("Fecha: %s\n\n", usuari->publicacions[i].data);
        printf("Contenido:\n%s\n\n", usuari->publicacions[i].contingut);
        printf("Likes: %d\n", usuari->publicacions[i].mAgrada);
        printf("---------------------------------------------------\n");

        int opcio = entradaInt("Vols donar m'agrada a aquesta publicació? (1: Sí, 0: No)");

        if (opcio == 1) {
            usuari->publicacions[i].mAgrada++;
            printf("Has donat m'agrada a aquesta publicació.\n");
        }
        printf("\n");
    }
}