//Includes
#include "global.h"

extern int name_filter(char name[]);
extern int user_filter(char user[]);
extern int city_filter(char city[]);
extern int mail_filter(char mail[]);


// Aquesta funció serveix perquè l'usuari introdueixi un enter, el paràmetre és per imprimir un missatge per l'usuari.
// retorna
int entradaInt(char missatge[]) {
    int nombreEnter;
    printf("%s: ", missatge);
    fflush(stdout);

    while (scanf("%d", &nombreEnter) != 1) {
        printf("Error: S'esperava un numero enter.\n");
        fflush(stdin);

        printf("%s: ", missatge);
        fflush(stdout);
    }

    printf("\n");
    return nombreEnter;
}

int entradaString(char missatge[], char entradaUsuari[], char filtres[]) {
    int i = 0;

    while (i == 0){
        printf("%s", missatge);
        if(strcmp(filtres, "none") == 0){
            scanf(" %[^\n]", entradaUsuari);
            i = 1;
        } else if ((strcmp(filtres, "name") == 0)){
            scanf(" %[^\n]", entradaUsuari);
            i = name_filter(entradaUsuari);
        } else if ((strcmp(filtres, "user") == 0)){
            scanf(" %[^\n]", entradaUsuari);
            i = user_filter(entradaUsuari);
        } else if ((strcmp(filtres, "city") == 0)){
            scanf(" %[^\n]", entradaUsuari);
            i = city_filter(entradaUsuari);
        } else if ((strcmp(filtres, "mail") == 0)){
            scanf(" %[^\n]", entradaUsuari);
            i = mail_filter(entradaUsuari);
        }
    }

    return i;
}
