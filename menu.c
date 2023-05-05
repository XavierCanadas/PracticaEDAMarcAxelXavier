#include "menu.h"
#include "structs.h"

// Aquesta funció conté el bucle del menú del programa.
int bucleMenu() {

    int opcioEscollida = 0;

    // Es mostra el menú d'opcions
    showMenuOptions();

    while (opcioEscollida != SORTIR) {
        opcioEscollida = entradaInt();

        switch (opcioEscollida) {
            case NOU_USUARI:
                printf("Crida funció nou usuari\n");

                break;

            case LLISTA_USUARIS:
                printf("Crida funció llista usuaris\n");

                break;

            case ESCOLLIR_USUARI:
                printf("Crida funció escollir usuari\n");

                break;

            case MOSTRAR_OPCIONS:
                showMenuOptions();

                break;

            default:
                printf("Ha introduït una opció invàlida!\n");
                break;
        }
    }
    printf("Adeu!\n");

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

int entradaInt(){
    int nombreEnter;

    if (scanf("%d", &nombreEnter) != ERROR_ENTRADA_DADES) return nombreEnter;

    flush_input();

    return OPCIO_INVALIDA;
}

// Aquesta funció estava a la pràctica d'EDA-I, si no s'executa al final de trucar a "scanf" poden sortir bugs
// que facin que hi hagi bucles infinits en el menú.
void flush_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int NouUsuari(){
    Usuari user;
    printf("Introdueixi el seu nom: \n");
    scanf("%s",)
}
