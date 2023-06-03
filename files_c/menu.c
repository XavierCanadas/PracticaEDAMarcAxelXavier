#include "../files_h/menu.h"

// Aquesta funció conté el bucle del menú del programa.
int bucleMenu() {

    // Es crea la taula hash
    TaulaHash* taulaHash = (TaulaHash*) malloc(sizeof(TaulaHash));
    initTaulaHash(taulaHash, 10);

    int opcioEscollida = 0;

    while (opcioEscollida != SORTIR) {
        // Es mostra el menú d'opcions
        showMenuOptions();
        opcioEscollida = 0;

        printf("\n");
        opcioEscollida = entradaInt("Si us plau, seleccioni una opció");

        /* Aquest bucle no és necessari ja que si passa això s'executarà el que posa
         * a l'apartat default del switch.
        while(opcioEscollida < 1 || opcioEscollida > 5) {
            opcioEscollida = entradaInt("\nSi us plau, seleccioni una opcio del menu");
        }
         */
        Usuari* usuariAux = NULL;
        int codiGuardarUsuari = ERROR_GUARDAR_USUARU;

        switch (opcioEscollida) {
            case NOU_USUARI:

                usuariAux = nouUsuari();
                while (codiGuardarUsuari == ERROR_GUARDAR_USUARU) {
                    codiGuardarUsuari = guardarUsuari(usuariAux, usuariAux->nomUsuari, taulaHash, NULL);
                    if (codiGuardarUsuari != SUCCESS) {
                        if (taulaHashPlena(taulaHash) == ERROR_AMPLIAR_TAULA) {
                            printf("Hi ha hagut un error al ampliar la taula\n");
                            break;
                        }
                    }

                }
                break;

            case LLISTA_USUARIS:
                imprimirUsuaris(taulaHash);
                break;

            case ESCOLLIR_USUARI:
                bucleEscollirUsuari(taulaHash);
                break;

            case MOSTRAR_OPCIONS:
                break;

            case SORTIR:
                eliminarTaulaHash(taulaHash);
                break;

            default:
                printf("Ha introduït una opció invàlida!\n");
                break;
        }
        fflush(stdout);
    }
    printf("\nAdeu!\n");
    fflush(stdout);

    return SUCCESS;
}

int bucleEscollirUsuari(TaulaHash* taula) {
    int opcioEscollida = 0;
    int entradaAuxEliminarUsuari = 0;

    char user[MAX_STRING];
    entradaString("Introduiu el nom d'usuari amb el que volgueu operar: ", user, "none");
    Usuari *usuari = buscarUsuari(taula, user);
    while (usuari == NULL) {
        entradaString("Usuari invàlid, introduiu un altre nom: ", user, "none");
        usuari = buscarUsuari(taula, user);
    }
    // Es mostra el menú d'opcions
    showEscollirUsuaruMenu();
    while (opcioEscollida != SORTIR) {
        opcioEscollida = entradaInt("Si us plau, seleccioni una opció");

        switch (opcioEscollida) {
            case GESTIONAR_SOLICITUTS:
                gestionSolicitudesAmistad(usuari);

                break;
            case FER_PUBLICACIO:
                printf("fer publicació\n");

                break;
            case VEURE_PUBLICACIONS:
                printf("veure publicacions d'un usuari");
                break;
            case MOSTRAR_OPCIONS:
                showEscollirUsuaruMenu();
            case EDITAR_USUARI:
                printf("/do s'editaria l'usuari ");
                break;

            case ELIMINAR_USUARI:
                printf("Estàs segur que vols borrar?\n escrigui %d per confirmar o %d per cancelar\n",CONFIRMAR, CANCELAR);
                fflush(stdout);
                entradaAuxEliminarUsuari = entradaInt("Entri la seva resposta");
                if (entradaAuxEliminarUsuari == CONFIRMAR) {
                    eliminarUsuari(taula, hashing(usuari->nomUsuari, taula, false));
                    printf("L'usuari s'ha borrat amb èxit\n");
                    opcioEscollida = SORTIR;

                } else {
                    printf("S'ha cancelat l'eliminació\n");
                }
                break;

            default:
                printf("Ha introduït una opció invàlida!\n");
                break;
        }
        fflush(stdout);
    }
    printf("Has sortit del menú d'usuari\n");

    return SUCCESS;
}


// Aquesta funció servirà per ensenyar les opcions que hi ha en el menú.
void showMenuOptions() {
    printf("Esculli una de les següents opcions:\n");
    printf("\t %d: Crear nou usuari.\n", NOU_USUARI);
    printf("\t %d: Llistar tots els usuaris guardats.\n", LLISTA_USUARIS);
    printf("\t %d: Escollir un usuari\n", ESCOLLIR_USUARI);
    printf("\t %d: Mostrar opcions.\n", MOSTRAR_OPCIONS);
    printf("\t %d: Sortir.\n", SORTIR);
    fflush(stdout);
}

// Imprimeix el menú del bucle de l'opció escollir usuari
void showEscollirUsuaruMenu() {
    printf("Esculli una de les següents opcions:\n");
    printf("\t %d: Gestionar o enviar solicituts d'amistat.\n", GESTIONAR_SOLICITUTS);
    printf("\t %d: Fer una publicació\n", FER_PUBLICACIO);
    printf("\t %d: Veure les publicacions.\n", VEURE_PUBLICACIONS);
    printf("\t %d: Editar l'usuari\n", ELIMINAR_USUARI);
    printf("\t %d: Eliminar l'usuari\n", ELIMINAR_USUARI);
    printf("\t %d: Mostrar opcions.\n", MOSTRAR_OPCIONS);
    printf("\t %d: Sortir.\n", SORTIR);
    fflush(stdout);
}
