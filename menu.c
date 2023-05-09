#include "menu.h"
#include "structs.h"



// es crea l'Array d'usuaris


// Aquesta funció conté el bucle del menú del programa.
int bucleMenu() {

    Usuari *llistaUsuaris = (Usuari*) malloc(sizeof(Usuari));

    int opcioEscollida = 0;

    // Es mostra el menú d'opcions
    showMenuOptions();

    while (opcioEscollida != SORTIR) {
        opcioEscollida = entradaInt("Si us plau, seleccioni una opció");

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

// Aquesta funció servirà per ensenyar les opcions que hi ha en el menú.
void showMenuOptions() {
    printf("Esculli una de les següents opcions:\n");
    printf("\t %d: crear nou usuari.\n", NOU_USUARI);
    printf("\t %d: llista de tots els usuaris guardats.\n", LLISTA_USUARIS);
    printf("\t %d: escollir un usuari\n", ESCOLLIR_USUARI);
    printf("\t %d: mostrar opcions.\n", MOSTRAR_OPCIONS);
    printf("\t %d: sortir.\n", SORTIR);
}



int nouUsuari() {
    Usuari *user = (Usuari*) malloc(sizeof(Usuari));
    entradaString("Introdueixi el seu nom: ",user->nom );
    entradaString("Introdueixi la seva ciutat: ",user->ciutat);
    entradaString("Introdueixi el seu correu: ",user->correu);
    user->edat= entradaInt("Introdueixi la seva edat: ");
    for (int i=0;i<5;i++){
        entradaString("Introdueixi un gust: ",user->gustos[i]);
        if (user->gustos[i]=="");
    }
    return SUCCESS;
}

int entradaNouUsuari() {

}
