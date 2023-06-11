#include "../files_h/publicacions.h"

///Funcions per les publicacions
#include <time.h>


// S'inicialitza l'array de publicacions
/**
 * Es reserva a memòria espai per un objecte ArrayPublciacions i també es reserva espai per un array de punters de Publicació.
 * @param mida
 * @return
 */
ArrayPublciacions* initArrayPublicacions(int mida) {
    ArrayPublciacions* arrayPublciacions = (ArrayPublciacions*) calloc(1, sizeof(ArrayPublciacions));
    arrayPublciacions->mida = mida;
    arrayPublciacions->nombrePublicacions = 0;
    arrayPublciacions->publicacions = (Publicacio**) calloc(mida, sizeof(Publicacio*));

    return arrayPublciacions;
}
/**
 * Quan l'array de punters de Publicació  s'emplena, aquesta funció amplia l'array.
 * @param novaMida
 * @param arrayPublciacions
 * @return
 */
int ampliarArrayPublicacions(int novaMida, ArrayPublciacions* arrayPublciacions) {
    Publicacio** aux;
    int midaAux = arrayPublciacions->mida;
    aux = (Publicacio**) realloc(arrayPublciacions->publicacions, novaMida*sizeof(Publicacio*));

    if (arrayPublciacions == NULL) {
        return ERROR_AMPLIAR_TAULA;
    }
    arrayPublciacions->publicacions = aux;

    arrayPublciacions->mida = novaMida;

    for (int i = midaAux-1; i < novaMida; ++i) {
        arrayPublciacions->publicacions[i] = NULL;
    }

    return SUCCESS;
}
/**
 * Es llibera de memòria totes les publicacions i també l'array de publicacions passat.
 * @param arrayPublciacions
 */
void freeArrayPublicacions(ArrayPublciacions* arrayPublciacions) {
    for (int i = 0; i < arrayPublciacions->mida; ++i) {
        if (arrayPublciacions->publicacions[i] != NULL)
            free(arrayPublciacions->publicacions[i]);
    }
    free(arrayPublciacions);
}
/**
 * S'inicialitza la llista que conté les tendències. Aquesta llista pot ser de dos tipus: llista normal o una
 * taula hash, l'única diferència, en aquest cas, és la manera en què s'afegeixen els valors a la llista.
 * @param mida
 * @return
 */
ArrayTendencies* initArrayTendencies(int mida) {
    ArrayTendencies* arrayTendencies = (ArrayTendencies*) calloc(1, sizeof(ArrayPublciacions));
    arrayTendencies->mida = mida;
    arrayTendencies->nombreTendencies = 0;
    arrayTendencies->tendencies = (Tendencia**) calloc(mida, sizeof(Tendencia*));
    return arrayTendencies;
}
/**
 * Quan la llista de tendències s'emplena, aquesta funció amplia la llista. Si és de tipus taulahash es tornen
 * a calcular l'índex de cada objecte de Tendecia.
 * @param novaMida
 * @param arrayTendencies
 * @param taulaHash
 * @return
 */
int ampliarArraytendencies(int novaMida, ArrayTendencies* arrayTendencies, bool taulaHash) {
    Tendencia** aux;
    int midaAux = arrayTendencies->mida - 1;

    aux = (Tendencia**) realloc(arrayTendencies->tendencies, novaMida*sizeof(Tendencia*));

    if (arrayTendencies == NULL) {
        return ERROR_AMPLIAR_TAULA;
    }
    arrayTendencies->tendencies = aux;
    arrayTendencies->mida = novaMida;

    if (taulaHash == false) {
        for (int i = midaAux; i < novaMida; ++i) {
            arrayTendencies->tendencies[i] = NULL;
        }
    } else {
        for (int i = novaMida - 1; i >= 0; --i) {
            if (i >= novaMida - 10) {
                arrayTendencies->tendencies[i] = NULL;
            } else {
                int indexGuardat;
                indexGuardat = hashingTendencies(arrayTendencies, arrayTendencies->tendencies[i]);
                if (indexGuardat != i) {
                    arrayTendencies->tendencies[indexGuardat] = arrayTendencies->tendencies[i];
                    arrayTendencies->tendencies[i] = NULL;
                }
            }
        }
    }
    return SUCCESS;
}
/**
 * Es llibera de memòria totes les tendències i també l'array de tendències
 * @param arrayTendencies
 */
void freeArrayTendencies(ArrayTendencies* arrayTendencies) {
    for (int i = 0; i < arrayTendencies->mida; ++i) {
        if (arrayTendencies->tendencies[i] != NULL)
            free(arrayTendencies->tendencies[i]);
    }
    free(arrayTendencies);
}
/**
 * Aquesta funció és la mateixa que la funció de hashing() pels usuari però adaptada a l'objecte Tendències.
 * Té la mateixa funcionalitat.
 * @param arrayTendencies
 * @param tendencia
 * @return
 */
int hashingTendencies(ArrayTendencies* arrayTendencies, Tendencia* tendencia) {
    int index, i = 0;
    int clauASCII = charToIntASCII(tendencia->contingut);
    char clauAux[MAX_STRING];

    do {
        // S'aplica el mòdul al nombre clauASCII % mida de la taula
        index = (clauASCII + i) % arrayTendencies->mida;
        // Agafa la clau guardada a la posició de l'índex trobat per després comparar.
        if (arrayTendencies->tendencies[index] == NULL)
            break;
        strcpy(clauAux, arrayTendencies->tendencies[index]->contingut);


        // Es complirà quan s'ha recorregut tota la taula
        if (i == arrayTendencies->mida) {
            return ERROR_CALCULAR_INDEX;
        }
        i++;
    } while (strcmp("", clauAux) != 0 && strcmp(tendencia->contingut, clauAux) != 0);

    return index;
}

/**
 * Aquesta funció conté l'algoritme d'insertionSort que ordenarà les tendències de major a menor.
 * @param arrayTendenciesSorting
 * @param n
 */
void insertionSort(ArrayTendencies* arrayTendenciesSorting, int n) {
    int  j;
    Tendencia *key;
    for (int i = 1; i < arrayTendenciesSorting->nombreTendencies; i++) {
        key = arrayTendenciesSorting->tendencies[i];
        j = i - 1;
        while (j >= 0 && arrayTendenciesSorting->tendencies[j]->popularitat < key->popularitat) {
            arrayTendenciesSorting->tendencies[j + 1] = arrayTendenciesSorting->tendencies[j];
            j = j - 1;
        }
        arrayTendenciesSorting->tendencies[j + 1] = key;
    }

}
/**
 * Per afegir guardar les tendències hem usat dos arrays de punters. el primer el tractem com una taulaHash per poder
 * trobar ràpidament les paraules i portar el comtatge de quantes vegades han sortit trucuant a ujna funció de hash. El
 * segon array conté punters a les tendències que hi ha a la taula hash anterior però en aquest array s'ordenen de major a menor
 * fent servir l'algoritme d'insertionSort.
 * @param publicacio
 * @param arrayTendencies
 * @param arrayTendenciesSorting
 */
void afegirTendencies(Publicacio* publicacio, ArrayTendencies* arrayTendencies, ArrayTendencies* arrayTendenciesSorting) {

    // Separar el contingut d'una publicació en paraules
    char* ultimaPosicio;
    char* paraula = strtok_r(publicacio->contingut, " ", &ultimaPosicio);


    while (paraula != NULL) {
        Tendencia* tendencia = (Tendencia*) calloc(1, sizeof(Tendencia));
        strcpy(tendencia->contingut, paraula);
        bool trobat = false;
        // Comproba que la paraula té més de 2 lletres
        if (strlen(paraula) > 2) {
            int index = hashingTendencies(arrayTendencies, tendencia);
            if (arrayTendencies->tendencies[index] != NULL && strcmp(tendencia->contingut, arrayTendencies->tendencies[index]->contingut) == 0) {
                arrayTendencies->tendencies[index]->popularitat += 1;
            } else {
                tendencia->popularitat = 1;
                if (arrayTendencies->mida == (arrayTendencies->nombreTendencies -1 ))
                    ampliarArraytendencies(arrayTendencies->mida+10, arrayTendencies, true);
                arrayTendencies->tendencies[index] = tendencia;
                arrayTendencies->nombreTendencies++;

                if (arrayTendenciesSorting->mida == (arrayTendenciesSorting->nombreTendencies -1 ))
                    ampliarArraytendencies(arrayTendenciesSorting->mida+10, arrayTendenciesSorting, false);
                arrayTendenciesSorting->tendencies[arrayTendenciesSorting->nombreTendencies] = tendencia;
                arrayTendenciesSorting->nombreTendencies++;
            }

        }
        // Això passa a la següent paraula de la publicació
        paraula = strtok_r(NULL, " ", &ultimaPosicio);
    }

}
/*
 * Aquesta funció recorre totes les publicacions que ja estan creades i guarda les paraules a tendències.
 * La funció es truca una vegada agafades les dades del json.
 */
void agafarTendenciesvoid(ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendencies, ArrayTendencies* arrayTendenciesSorting) {
    for (int i = 0; i < arrayPublciacions->nombrePublicacions; ++i) {
        if (arrayPublciacions->publicacions[i] != NULL && arrayPublciacions->publicacions[i]->contingut[0] != '\0') {
            afegirTendencies(arrayPublciacions->publicacions[i], arrayTendencies, arrayTendenciesSorting);
        }
    }
}

/**
 * La funció imprimeix les tendències de major a menor vegades que han sortit.
 * @param arrayPublciacions
 * @param arrayTendenciesSorting
 */
void imprimirTendenciesFinal(ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendenciesSorting) {
    insertionSort(arrayTendenciesSorting,arrayTendenciesSorting->nombreTendencies);
    printf("------------------------------------\n"
           "               TENDENCIES              \n"
           "---------------------------------------\n");
    for(int a = 0; a < 6;a++){
        if (arrayTendenciesSorting->tendencies[a] != NULL)
            printf("-> %s (%d vegades)\n",arrayTendenciesSorting->tendencies[a]->contingut,arrayTendenciesSorting->tendencies[a]->popularitat);
    }
}


/**
 * Aquesta funció s'encarrega de crear una Publicació, demana a l'usuari que entri el contingut i guarda la data en què s'ha fet.
 *
 * @param usuari
 * @param arrayPublciacions
 * @param arrayTendencies
 * @param arrayTendenciesSorting
 * @return
 */
int realitzarPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendencies,ArrayTendencies* arrayTendenciesSorting) {
    char contingut[MAX_STRING];
    memset(contingut, 0, sizeof(contingut));
    printf("Introdueix el contingut de la publicacio (maxim %d caracters): ", MAX_CARACTERS);
    fflush(stdout);
    entradaString(" ", contingut, "none");

    // Obtener la fecha actual
    time_t t = time(NULL);
    struct tm* fecha = localtime(&t);

    // Formatear la fecha en el formato deseado (dd/mm/aaaa)
    char data[MAX_STRING];
    snprintf(data, sizeof(data), "%02d/%02d/%d", fecha->tm_mday, fecha->tm_mon + 1, fecha->tm_year + 1900);

    afegirPublicacio(usuari, arrayPublciacions, contingut, data, 0, arrayTendencies, arrayTendenciesSorting);

    printf("Publicacio realitzada amb exit.\n");
    return SUCCESS;
}
/**
 * Aquesta funció s'encarrega de posar la publicació a l'array de publicacions de l'usuari que l'ha fet i també
 * a l'array que conté totes les publicacions. També, una vegada creada la publicació es truca a la funció d'afegir tendència per
 * portar el recompte de paraules que han sortit més.
 * @param usuari
 * @param arrayPublciacions
 * @param contingut
 * @param data
 * @param likes
 * @param arrayTendencies
 * @param arrayTendenciesSorting
 */
void afegirPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions, char* contingut, char* data, int likes, ArrayTendencies* arrayTendencies,ArrayTendencies* arrayTendenciesSorting) {
    Publicacio* publicacio = (Publicacio*) calloc(1, sizeof(Publicacio));
    if (arrayPublciacions->mida == (arrayPublciacions->nombrePublicacions-1))
        ampliarArrayPublicacions(arrayPublciacions->mida+10, arrayPublciacions);

    if (usuari->arrayPublciacions->mida == (usuari->arrayPublciacions->nombrePublicacions-1))
        ampliarArrayPublicacions(usuari->arrayPublciacions->mida+10, usuari->arrayPublciacions);

    strcpy(publicacio->contingut, contingut);
    publicacio->likes = likes;

    strcpy(publicacio->data, data);
    strcpy(publicacio->nomUsuari, usuari->nomUsuari);
    usuari->arrayPublciacions->publicacions[usuari->nombrePublicacions] = publicacio;
    arrayPublciacions->publicacions[arrayPublciacions->nombrePublicacions] = publicacio;
    arrayPublciacions->nombrePublicacions++;

    usuari->nombrePublicacions++;

    if (arrayTendencies != NULL && arrayTendenciesSorting != NULL)
        afegirTendencies(publicacio, arrayTendencies,arrayTendenciesSorting);

}

/**
 * Aquesta funció conté el bucle del menú de publicacions i les diferentes opcions que es poden fer.
 * @param arrayPublciacions
 * @param usuari
 * @param arrayTendencies
 * @param arrayTendenciesSorting
 */
void mostrarPublicacions(ArrayPublciacions* arrayPublciacions, Usuari* usuari, ArrayTendencies* arrayTendencies,ArrayTendencies* arrayTendenciesSorting) {
    int entradaUsuari = 0;
    int nombrePublicacions;
    printf("\n-----------------------------------------\n");
    printf("        PUBLICACIONS\n");
    printf("-----------------------------------------\n");
    while (entradaUsuari != 3) {
        printf("\t %d: Veure les teves publicacions\n"
               "\t %d: Veure totes les publicacions\n"
               "\t %d: Tendencies\n"
               "\t %d: Sortir",VEURE_MEVES_PUB, VEURE_TOTES_PUB, TENDENCIES, SORTIR_PUB);
        entradaUsuari = entradaInt(" ");
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
                    publicacio = usuari->arrayPublciacions->publicacions[i];
                    break;

                case 2:
                    publicacio = arrayPublciacions->publicacions[i];
                    break;
                case 3:
                    imprimirTendenciesFinal(arrayPublciacions, arrayTendenciesSorting);
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
            printf("Publicacio feta per: %s\n", publicacio->nomUsuari);
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





