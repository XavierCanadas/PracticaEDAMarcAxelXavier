#include "menu.h"
#include "structs.h"


// Aquesta funció conté el bucle del menú del programa.
int bucleMenu() {

    // es crea l'Array d'usuaris
    LlistaUsers llistaUsuaris;
    llistaUsuaris.llista = (Usuari*) malloc(10*sizeof(Usuari));
    llistaUsuaris.num_users=0;

    int opcioEscollida = 0;

    // Es mostra el menú d'opcions
    showMenuOptions();

    while (opcioEscollida != SORTIR) {
        opcioEscollida = entradaInt("Si us plau, seleccioni una opció");

        switch (opcioEscollida) {
            case NOU_USUARI:
                if(llistaUsuaris.num_users % 10 == 0){
                    realloc(llistaUsuaris.llista,10*llistaUsuaris.num_users*sizeof(Usuari));
                }
                llistaUsuaris.llista[llistaUsuaris.num_users]=*nouUsuari();
                llistaUsuaris.num_users ++;
                break;

            case LLISTA_USUARIS:
                printUsers(&llistaUsuaris);

                break;

            case ESCOLLIR_USUARI:
                printf("Crida funció escollir usuari\n");
                bucleEscollirUsuari();
                break;

            case MOSTRAR_OPCIONS:
                showMenuOptions();
                break;

            case SORTIR:
                break;

            default:
                printf("Ha introduït una opció invàlida!\n");
                break;
        }
    }
    printf("\nAdeu!\n");

    return SUCCESS;
}
int bucleEscollirUsuari() {
    int opcioEscollida = 0;

    // Es mostra el menú d'opcions
    showEscollirUsuaruMenu();

    while (opcioEscollida != SORTIR) {
        opcioEscollida = entradaInt("Si us plau, seleccioni una opció");

        switch (opcioEscollida) {
            case ENVIAR_SOLICITUD:
                printf("enviar solicitud\n");

                break;
            case GESTIONAR_SOLICITUTS:
                printf("gestionar solicituds\n");

                break;
            case FER_PUBLICACIO:
                printf("fer publicació\n");

                break;
            case VEURE_PUBLICACIONS:
                printf("veure publicacions d'un usuari");
                break;
            case MOSTRAR_OPCIONS:
                showEscollirUsuaruMenu();
            default:
                printf("Ha introduït una opció invàlida!\n");
                break;
        }
    }
    return SUCCESS;
}


// Aquesta funció servirà per ensenyar les opcions que hi ha en el menú.
void showMenuOptions() {
    printf("Esculli una de les següents opcions:\n");
    printf("\t %d: crear nou usuari.\n", NOU_USUARI);
    printf("\t %d: llista de tots els usuaris guardats.\n", LLISTA_USUARIS);
    printf("\t %d: escollir un usuari\n", ESCOLLIR_USUARI);
    printf("\t %d: mostrar opcions.\n", MOSTRAR_OPCIONS);
    printf("\t %d: sortir.\n", SORTIR);
}

// Imprimeix el menú del bucle de l'opció escollir usuari
void showEscollirUsuaruMenu() {
    printf("Esculli una de les següents opcions:\n");
    printf("\t %d: enviar una solicitut d'amistat.\n", ENVIAR_SOLICITUD);
    printf("\t %d: gestiona les teves solicituts d'amistat.\n", GESTIONAR_SOLICITUTS);
    printf("\t %d: fer una publicació\n", FER_PUBLICACIO);
    printf("\t %d: veure les publicacions.\n", VEURE_PUBLICACIONS);
    printf("\t %d: mostrar opcions.\n", MOSTRAR_OPCIONS);
    printf("\t %d: sortir.\n", SORTIR);
}

Usuari* nouUsuari() {
    Usuari *user = (Usuari *) malloc(sizeof(Usuari));
    entradaString("Introdueixi el seu nom: ", user->nom);
    entradaString("Introdueixi la seva ciutat: ", user->ciutat);
    entradaString("Introdueixi el seu correu: ", user->correu);
    user->edat = entradaInt("Introdueixi la seva edat: ");
    for (int i = 0; i < 5; i++) {
        entradaString("Introdueixi un gust: ", user->gustos[i]);
        if (user->gustos[i] == "");
    }
    return user;
}

void printUsers(LlistaUsers* llista){
    for (int i = 0; i < llista->num_users; ++i) {
        printf("%s \n",llista->llista[i].nom);
    }
}

int entradaNouUsuari() {

}
