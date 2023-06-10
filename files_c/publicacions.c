#include "../files_h/publicacions.h"

///Funcions per les publicacions
#include <time.h>


// S'inicialitza l'array de publicacions
ArrayPublciacions* initArrayPublicacions(int mida) {
    ArrayPublciacions *arrayPublciacions = (ArrayPublciacions *) malloc(sizeof(ArrayPublciacions));
    arrayPublciacions->mida = mida;
    arrayPublciacions->nombrePublicacions = 0;
    arrayPublciacions->publicacions = (Publicacio **) calloc(mida, sizeof(Publicacio *));

    return arrayPublciacions;
}

char** separarParaules(const char *frase) {
    // Comptar el número de paraules a la frase
    int contador = 0;
    const char* p = frase;
    while (*p != '\0') {
        // Ignorar espais inicials
        while (*p == ' ') {
            p++;
        }
        // Comptar la paraula
        if (*p != '\0') {
            contador++;
            // Avançar fins al següent espai o final de la frase
            while (*p != ' ' && *p != '\0') {
                p++;
            }
        }
    }

    // Assignar memòria per a l'array de paraules
    char** paraules = (char**)malloc((contador + 1) * sizeof(char*));
    if (paraules == NULL) {
        return NULL;
    }

    // Copiar les paraules a l'array
    int index = 0;
    p = frase;
    while (*p != '\0') {
        // Ignorar espais inicials
        while (*p == ' ') {
            p++;
        }
        // Copiar la paraula
        if (*p != '\0') {
            const char* inici = p;
            // Avançar fins al següent espai o final de la frase
            while (*p != ' ' && *p != '\0') {
                p++;
            }
            const int longitud = p - inici;
            char* paraula = (char*)malloc((longitud + 1) * sizeof(char));
            if (paraula == NULL) {
                // Alliberar memòria si hi ha un error
                for (int i = 0; i < index; i++) {
                    free(paraules[i]);
                }
                free(paraules);
                return NULL;
            }
            strncpy(paraula, inici, longitud);
            paraula[longitud] = '\0';
            paraules[index] = paraula;
            index++;
        }
    }

    paraules[index] = NULL; // Marcar el final de l'array amb un punter nul
    return paraules;
}

void insertionSort(int array[], int n) {
    int i, j, valorActual;

    for (i = 1; i < n; i++) {
        valorActual = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > valorActual) {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = valorActual;
    }
}


void imprimirTendenciesFinal(Publicacio** publicacions) {
    Tendencia *tendencies = (Tendencia *) malloc(10 * sizeof(Tendencia));
    // Comptar la popularitat de cada tendència
    int i = 0;
    int j = 0;
    int numTendencies = 0;
    int k;
    while (publicacions[j]) {
        while (separarParaules(publicacions[j]->contingut)[i]);{
            k=0;
            char tendencia[MAX_STRING];
            strcpy(tendencia,separarParaules(publicacions[j]->contingut)[i]);
            while(k<numTendencies){
                if(strcmp(tendencies[k].contingut,tendencia)==0){
                    tendencies[k].popularitat++;
                    break;
                }
                k++;
            }
            numTendencies++;
            strcpy(tendencies[numTendencies].contingut,tendencia);
            tendencies[numTendencies].popularitat=1;
            i++;
        }
        i=0;
        j++;
    }
    insertionSort(&tendencies->popularitat,numTendencies);
    for(int a=0;a<numTendencies;a++){
        printf("------------------------------------\n"
               "               TENDENCIES              \n"
               "---------------------------------------\n"
               "%d: %s",a,tendencies[a].contingut);
    }
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
        entradaUsuari = entradaInt("[1]- Veure les teves publicacions\n"
                                   "[2]- Veure totes les publicacions\n"
                                   "[3]- Tendències\n"
                                   "[4]- Sortir\n");
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
                    imprimirTendenciesFinal(&publicacio);
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


