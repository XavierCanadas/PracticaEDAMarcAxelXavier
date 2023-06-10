#include "../files_h/publicacions.h"

///Funcions per les publicacions
#include <time.h>


// S'inicialitza l'array de publicacions
ArrayPublciacions* initArrayPublicacions(int mida) {
    ArrayPublciacions* arrayPublciacions = (ArrayPublciacions*) calloc(1, sizeof(ArrayPublciacions));
    arrayPublciacions->mida = mida;
    arrayPublciacions->nombrePublicacions = 0;
    arrayPublciacions->publicacions = (Publicacio**) calloc(mida, sizeof(Publicacio*));

    return arrayPublciacions;
}

char** separarParaules(const char* frase, int longitud) {
    // Assignar memòria per a l'array de paraules
    char** paraules = (char**)malloc((101) * sizeof(char*));
    if (paraules == NULL) {
        return NULL;
    }

    int contador = 0;  // Comptador de paraules
    int inici = 0;    // Índex d'inici d'una paraula

    for (int i = 0; i < longitud; i++) {
        if (frase[i] == ' ' || frase[i] == '\0') {
            // Trobem un espai en blanc o el final de la cadena
            if (i - inici > 0) {
                // La paraula té almenys un caràcter
                int longitudParaula = i - inici;
                char* paraula = (char*)malloc((longitudParaula + 1) * sizeof(char));
                if (paraula == NULL) {
                    // Error d'assignació de memòria
                    for (int j = 0; j < contador; j++) {
                        free(paraules[j]);
                    }
                    free(paraules);
                    return NULL;
                }

                strncpy(paraula, &frase[inici], longitudParaula);
                paraula[longitudParaula] = '\0';
                paraules[contador] = paraula;
                contador++;

                if (contador >= 100) {
                    // S'ha arribat al límit màxim de paraules
                    break;
                }
            }

            inici = i + 1;
       }
    }

    paraules[contador] = NULL;  // Marcar el final de l'array amb un punter nul
    return paraules;
}


void insertionSort(Tendencia* tendencia, int n) {

    for (int i = 1; i < n; i++) {
        Tendencia valorActual = tendencia[i];
        int j = i - 1;

        while (j >= 0 && tendencia[j].popularitat < valorActual.popularitat) {
            tendencia[j + 1].popularitat = tendencia[j].popularitat;
            strcpy(tendencia[j+1].contingut,tendencia[j].contingut);
            j--;
        }
        tendencia[j + 1].popularitat = valorActual.popularitat;
        strcpy(tendencia[j+1].contingut,valorActual.contingut);
    }

}


void imprimirTendenciesFinal(ArrayPublciacions* arrayPublciacions) {
    int midaArrayTendencies = 10, numTendencies = 0;

    Tendencia* tendencies = (Tendencia *) calloc(midaArrayTendencies, sizeof(Tendencia));
    Publicacio** publicacions = arrayPublciacions->publicacions;

    // Recorrer totes les publicacions.
    for (int i = 0; i < arrayPublciacions->nombrePublicacions; ++i) {
        // Separar el contingut d'una publicació en paraules
        char* ultimaPosicio;
        char* paraula = strtok_r(publicacions[i]->contingut, " ", &ultimaPosicio);
        while (paraula != NULL) {
            bool trobat = false;
            // Comproba que la paraula té més de 2 lletres
            if (strlen(paraula) > 2) {
                // Recorre l'array de tendències per veure si està
                for (int j = 0; j < numTendencies; ++j) {
                    if (strcmp(tendencies[j].contingut, paraula) == 0){
                        tendencies[j].popularitat++;
                        trobat = true;
                        break;
                    }
                }
                if (trobat == false) {
                    if (numTendencies == (midaArrayTendencies-1)) {
                        realloc(tendencies, (midaArrayTendencies + 10)* sizeof(Tendencia));
                        midaArrayTendencies += 10;
                    }
                    strcpy(tendencies[numTendencies].contingut, paraula);
                    tendencies[numTendencies].popularitat = 1;
                    numTendencies++;
                }
            }
            // Això passa a la següent paraula de la publicació
            paraula = strtok_r(NULL, " ", &ultimaPosicio);
        }
    }



    /*
    // Comptar la popularitat de cada tendència
    int i = 0;
    int j = 0;
    int numTendencies = 0;
    int k;
    while (publicacions[j]) {
        char** palabras = separarParaules(publicacions[j]->contingut, (int) strlen(publicacions[j]->contingut));
        while (palabras != NULL && palabras[i]){
            k=0;
            char tendencia[MAX_STRING];
            strncpy(tendencia,separarParaules(publicacions[j]->contingut,strlen(publicacions[j]->contingut))[i],strlen(publicacions[j]->contingut));
            while(k<numTendencies){
                if(strcmp(tendencies[k].contingut,tendencia)==0){
                    tendencies[k].popularitat++;
                    break;
                }
                k++;
            }
            numTendencies++;
            strcpy(tendencies[numTendencies].contingut, tendencia);
            tendencies[numTendencies].popularitat=1;
            i++;
        }
        i=0;
        j++;
    }*/

    // L'he comentat per veure si s'imprimien les tendències.
    insertionSort(tendencies,arrayPublciacions->nombrePublicacions);
    printf("------------------------------------\n"
           "               TENDENCIES              \n"
           "---------------------------------------\n");
    for(int a=0;a<5;a++){
        printf("-> %s (%d vegades)\n",tendencies[a].contingut,tendencies[a].popularitat);
    }
}

int ampliarArrayPublicacions(int novaMida, ArrayPublciacions* arrayPublciacions) {
    Publicacio** aux;


    aux = (Publicacio**) realloc(arrayPublciacions->publicacions, novaMida*sizeof(Publicacio**));

    if (arrayPublciacions == NULL) {
        return ERROR_AMPLIAR_TAULA;
    }
    arrayPublciacions->publicacions = aux;
    arrayPublciacions->mida = novaMida;

    return SUCCESS;
}



int realitzarPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions) {
    char contingut[MAX_STRING];
    memset(contingut, 0, sizeof(contingut));
    printf("Introdueix el contingut de la publicacio (maxim %d caracters): ", MAX_CARACTERS);
    fflush(stdout);
    entradaString(" ", contingut, "none");

    Publicacio* aux;

    if (arrayPublciacions->mida == (arrayPublciacions->nombrePublicacions-1))
        ampliarArrayPublicacions(arrayPublciacions->mida+10, arrayPublciacions);

    strcpy(usuari->publicacions[usuari->nombrePublicacions].contingut, contingut);
    usuari->publicacions[usuari->nombrePublicacions].likes = 0;

    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm* fecha = localtime(&t);

    // Formatear la fecha en el formato deseado (dd/mm/aaaa)
    snprintf(usuari->publicacions[usuari->nombrePublicacions].data, sizeof(usuari->publicacions[usuari->nombrePublicacions].data), "%02d/%02d/%d", fecha->tm_mday, fecha->tm_mon + 1, fecha->tm_year + 1900);

    arrayPublciacions->publicacions[arrayPublciacions->nombrePublicacions] = &usuari->publicacions[usuari->nombrePublicacions];
    arrayPublciacions->nombrePublicacions++;

    usuari->nombrePublicacions++;

    printf("Publicacio realitzada amb exit.\n");
    return SUCCESS;
}


void mostrarPublicacions(ArrayPublciacions* arrayPublciacions, Usuari* usuari) {
    int entradaUsuari = 0;
    int nombrePublicacions;

    while (entradaUsuari != 3) {
        entradaUsuari = entradaInt("[1]- Veure les teves publicacions\n"
                                   "[2]- Veure totes les publicacions\n"
                                   "[3]- Tendències\n"
                                   "[4]- Sortir\n");
        if (entradaUsuari == 1)
            nombrePublicacions = usuari->nombrePublicacions;
        else
            nombrePublicacions = arrayPublciacions->nombrePublicacions;

        Publicacio* publicacio;

        if (nombrePublicacions == 0)
            printf("No hi ha publicacions.\n");

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
                    imprimirTendenciesFinal(arrayPublciacions);
                case 4:
                    return;
                default:
                    printf("Has entrat una opció incorrecte\n");
            }

            printf("---------------------------------------------------\n");
            printf("                Publicacio %d\n", i + 1);
            printf("---------------------------------------------------\n");
            printf("Data: %s\n\n", publicacio->data);
            printf("Contingut:\n%s\n\n", publicacio->contingut);
            printf("Likes: %d\n", publicacio->likes);
            printf("---------------------------------------------------\n");

            int opcio = entradaInt("Vols donar m'agrada a aquesta publicació? (1: Sí, 0: No)");

            if (opcio == 1) {
                publicacio->likes++;
                printf("Has donat m'agrada a aquesta publicació.\n");
            }

            printf("\n");
        }
    }


}


void freeArrayPublicacions(ArrayPublciacions* arrayPublciacions) {
    for (int i = 0; i < arrayPublciacions->mida; ++i) {
        if (arrayPublciacions->publicacions[i] != NULL)
            free(arrayPublciacions->publicacions[i]);
    }
    free(arrayPublciacions);
}


