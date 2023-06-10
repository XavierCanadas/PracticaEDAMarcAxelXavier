#include "../files_h/publicacions.h"

///Funcions per les publicacions
#include <time.h>


// S'inicialitza l'array de publicacions
ArrayPublciacions* initArrayPublicacions(int mida) {
    ArrayPublciacions* arrayPublciacions = (ArrayPublciacions*) malloc(sizeof(ArrayPublciacions));
    arrayPublciacions->mida = mida;
    arrayPublciacions->nombrePublicacions = 0;
    arrayPublciacions->publicacions = (Publicacio**) calloc(mida, sizeof(Publicacio*));

    return arrayPublciacions;
}

int ampliarArrayPublicacions(int novaMida, ArrayPublciacions* arrayPublciacions) {
    Publicacio** aux;

    aux = (Publicacio**) realloc(arrayPublciacions->publicacions, novaMida*sizeof(Publicacio**));

    if (arrayPublciacions == NULL) {
        return ERROR_AMPLIAR_TAULA;
    }
    arrayPublciacions->publicacions = aux;

    return SUCCESS;
}



int realitzarPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions) {
    char contingut[MAX_STRING];
    printf("Introdueix el contingut de la publicacio (maxim %d caracters): ", MAX_CARACTERS);
    fflush(stdout);
    entradaString("a", contingut, "none");

    Publicacio* aux;

    if (usuari->nombrePublicacions > 0) {
        aux = (Publicacio*) realloc(usuari->publicacions, sizeof(Publicacio)*(usuari->nombrePublicacions+1));

        if (arrayPublciacions == NULL) {
            return ERROR_AMPLIAR_TAULA;
        }
        usuari->publicacions = aux;
    }

    strcpy(usuari->publicacions[usuari->nombrePublicacions].contingut, contingut);
    usuari->publicacions[usuari->nombrePublicacions].mAgrada = 0;

    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm* fecha = localtime(&t);

    // Formatear la fecha en el formato deseado (dd/mm/aaaa)
    snprintf(usuari->publicacions[usuari->nombrePublicacions].data, sizeof(usuari->publicacions[usuari->nombrePublicacions].data), "%02d/%02d/%d", fecha->tm_mday, fecha->tm_mon + 1, fecha->tm_year + 1900);

    if (arrayPublciacions->mida == arrayPublciacions->nombrePublicacions) {

    }
    arrayPublciacions->publicacions[arrayPublciacions->nombrePublicacions] = &usuari->publicacions[usuari->nombrePublicacions];
    arrayPublciacions->nombrePublicacions++;

    usuari->nombrePublicacions++;

    printf("Publicacio realitzada amb exit.\n");
    return SUCCESS;
}


void mostrarPublicacions(ArrayPublciacions* arrayPublciacions, Usuari* usuari) {
    //char nomUsuari[MAX_STRING];
    //entradaString("Introdueix el nom d'usuari per mostrar les publicacions: ", nomUsuari, "none");
    int entradaUsuari = 0;
    int nombrePublicacions;




    while (entradaUsuari != 3) {
        entradaUsuari = entradaInt("Vols veure les teves publicacions [1], totes [2] o [3] per sortir");
        if (entradaUsuari == 1)
            nombrePublicacions = usuari->nombrePublicacions;
        else
            nombrePublicacions = arrayPublciacions->nombrePublicacions;

        Publicacio* publicacio;
        for (int i = 0; i < nombrePublicacions; i++) {

            switch (entradaUsuari) {
                case 1:
                    printf("Publicacions de l'usuari %s:\n", usuari->nomUsuari);
                    publicacio = &usuari->publicacions[i];
                    break;

                case 2:
                    publicacio = arrayPublciacions->publicacions[i];
                    break;
                case 3:
                    return;
                default:
                    printf("Has entrat una opció incorrecte\n");
            }

            printf("---------------------------------------------------\n");
            printf("                Publicacio %d\n", i + 1);
            printf("---------------------------------------------------\n");
            printf("Data: %s\n\n", publicacio->data);
            printf("Contingut:\n%s\n\n", publicacio->contingut);
            printf("Likes: %d\n", publicacio->mAgrada);
            printf("---------------------------------------------------\n");

            int opcio = entradaInt("Vols donar m'agrada a aquesta publicació? (1: Sí, 0: No)");

            if (opcio == 1) {
                publicacio->mAgrada++;
                printf("Has donat m'agrada a aquesta publicació.\n");
            }

            printf("\n");
        }
    }



    // Buscar l'usuari a partir del nom d'usuari proporcionat
    //Usuari* usuari = buscarUsuari(taula, nomUsuari);
    if (usuari == NULL) {
        printf("No s'ha trobat cap usuari amb aquest nom.\n");
        return;
    }

    printf("Publicacions de l'usuari %s:\n", usuari->nomUsuari);

    for (int i = 0; i < usuari->nombrePublicacions; i++) {
        printf("---------------------------------------------------\n");
        printf("                Publicacio %d\n", i + 1);
        printf("---------------------------------------------------\n");
        printf("Data: %s\n\n", usuari->publicacions[i].data);
        printf("Contingut:\n%s\n\n", usuari->publicacions[i].contingut);
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


void freeArrayPublicacions(ArrayPublciacions* arrayPublciacions) {
    for (int i = 0; i < arrayPublciacions->mida; ++i) {
        if (arrayPublciacions->publicacions[i] != NULL)
            free(arrayPublciacions->publicacions[i]);
    }
    free(arrayPublciacions);
}


