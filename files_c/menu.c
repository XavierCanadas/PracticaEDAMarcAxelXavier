#include "../files_h/menu.h"

// Aquesta funció conté el bucle del menú del programa.
int bucleMenu() {

    // Es crea la taula hash
    TaulaHash* taulaHash = (TaulaHash*) malloc(sizeof(TaulaHash));
    initTaulaHash(taulaHash, 10);

    ArrayPublciacions* arrayPublciacions = initArrayPublicacions(10);
    ArrayTendencies* arrayTendencies = initArrayTendencies(30);
    ArrayTendencies* arrayTendenciesSorting = initArrayTendencies(30);

    int opcioEscollida = 0;

    JsonObject* root = llegirFitxer("../dades.json");
    llegirUsuarisJson(taulaHash, root, arrayPublciacions);
    agafarTendenciesvoid(arrayPublciacions, arrayTendencies,arrayTendenciesSorting);

    borrarJsonObject(root);
    JsonObject* arrayUsuarisJson;
    char* rootGuardar;

    while (opcioEscollida != SORTIR) {

        // Es mostra el menú d'opcions
        showMenuOptions();

        opcioEscollida = entradaInt("Si us plau, seleccioni una opcio");

        Usuari* usuariAux = NULL;
        int codiGuardarUsuari = ERROR_GUARDAR_USUARU;

        switch (opcioEscollida) {
            case NOU_USUARI:

                usuariAux = nouUsuari();
                while (codiGuardarUsuari == ERROR_GUARDAR_USUARU) {
                    codiGuardarUsuari = guardarUsuari(usuariAux, usuariAux->nomUsuari, taulaHash, NULL);
                    if (codiGuardarUsuari != SUCCESS && taulaHashPlena(taulaHash) == ERROR_AMPLIAR_TAULA) {
                        printf("Hi ha hagut un error al ampliar la taula\n");
                        break;
                    }
                }
                break;

            case LLISTA_USUARIS:
                imprimirUsuaris(taulaHash);
                break;

            case ESCOLLIR_USUARI:
                bucleEscollirUsuari(taulaHash, arrayPublciacions, arrayTendencies, arrayTendenciesSorting);
                break;

            case MOSTRAR_OPCIONS:
                break;

            case SORTIR:
                arrayUsuarisJson = guardarUsuarisJson(taulaHash);

                eliminarTaulaHash(taulaHash);
                break;

            default:
                printf("Ha introduit una opcio invalida!\n");
                break;

        }
        fflush(stdout);
    }
    printf("\nAdeu!\n");
    printf("\033[2J");

    FILE* file = fopen("../dades.json", "w");
    rootGuardar = jsonObjectToString(arrayUsuarisJson, true, true,true);
    fputs(rootGuardar, file);
    fclose(file);

    borrarJsonObject(arrayUsuarisJson);
    free(rootGuardar);
    free(arrayPublciacions);
    freeArrayTendencies(arrayTendencies);
    free(arrayTendenciesSorting);


    fflush(stdout);

    return SUCCESS;
}

int bucleEscollirUsuari(TaulaHash* taula, ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendencies, ArrayTendencies* arrayTendenciesSorting) {
    int opcioEscollida = 0;
    int entradaAuxEliminarUsuari = 0;

    char user[MAX_STRING];
    entradaString("Introduiu el nom d'usuari amb el que volgueu operar: ", user, "none");
    Usuari *usuari = buscarUsuari(taula, user);
    while (usuari == NULL) {
        entradaString("Usuari invalid, introduiu un altre nom: ", user, "none");
        usuari = buscarUsuari(taula, user);
    }
    // Es mostra el menú d'opcions
    while (opcioEscollida != SORTIR_MENU_USUARI) {
        showEscollirUsuaruMenu(usuari);
        opcioEscollida = entradaInt("Si us plau, seleccioni una opcio");

        switch (opcioEscollida) {
            case GESTIONAR_SOLICITUTS:
                gestionSolicitudesAmistad(usuari,taula);
                break;

            case FER_PUBLICACIO:
                realitzarPublicacio(usuari, arrayPublciacions, arrayTendencies, arrayTendenciesSorting);
                break;

            case VEURE_PUBLICACIONS:
                mostrarPublicacions(arrayPublciacions, usuari, arrayTendencies, arrayTendenciesSorting);
                break;

            case EDITAR_USUARI:
                printf("S'editaria l'usuari\n");
                break;

            case ELIMINAR_USUARI:
                printf("Estàs segur que vols borrar?\n escrigui %d per confirmar o %d per cancelar\n",CONFIRMAR, CANCELAR);
                fflush(stdout);
                entradaAuxEliminarUsuari = entradaInt("Entri la seva resposta");
                if (entradaAuxEliminarUsuari == CONFIRMAR) {
                    eliminarUsuari(taula, hashing(usuari->nomUsuari, taula, false));
                    printf("L'usuari s'ha borrat amb èxit\n");
                    opcioEscollida = SORTIR;

                }
                else {
                    printf("S'ha cancelat l'eliminacio\n");
                }
                break;

            default:
                printf("Ha introduit una opcio invalida!\n");
                break;
        }
        fflush(stdout);
    }
    printf("Has sortit del menu d'usuari\n");

    return SUCCESS;
}


// Aquesta funció servirà per ensenyar les opcions que hi ha en el menú.
void showMenuOptions() {
    printf("\n-----------------------------------------\n");
    printf("           MENU PRINCIPAL\n");
    printf("-----------------------------------------\n");
    printf("Esculli una de les seguents opcions:\n");
    printf("\t %d: Crear nou usuari.\n", NOU_USUARI);
    printf("\t %d: Llistar tots els usuaris guardats.\n", LLISTA_USUARIS);
    printf("\t %d: Escollir un usuari.\n", ESCOLLIR_USUARI);
    printf("\t %d: Mostrar opcions.\n", MOSTRAR_OPCIONS);
    printf("\t %d: Sortir.\n", SORTIR);
    printf("-----------------------------------------\n");
    fflush(stdout);
}


// Imprimeix el menú del bucle de l'opció escollir usuari
void showEscollirUsuaruMenu(Usuari *usuari) {
    printf("\n-----------------------------------------\n");
    printf("        MENU %s\n", usuari->nomUsuari);
    printf("-----------------------------------------\n");
    printf("Esculli una de les seguents opcions:\n");
    printf("\t %d: Gestionar o enviar solicituts d'amistat.\n", GESTIONAR_SOLICITUTS);
    printf("\t %d: Fer una publicacio.\n", FER_PUBLICACIO);
    printf("\t %d: Veure les publicacions.\n", VEURE_PUBLICACIONS);
    printf("\t %d: Editar l'usuari.\n", EDITAR_USUARI);
    printf("\t %d: Eliminar l'usuari.\n", ELIMINAR_USUARI);
    printf("\t %d: Sortir.\n", SORTIR_MENU_USUARI);
    printf("-----------------------------------------\n");
    fflush(stdout);
}
