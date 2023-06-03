#include "../global.h"
//#include "../files_h/usuari.h"

int name_filter(char name[]){
    for (int i = 0; name[i] != '\0'; i++) {
        while (!isalpha(name[i])) {
            printf("El elemnto \"%c\", no es valido como parte del nombre\n", name[i]);
            return 0;
        }
    }
    return 1;  // La cadena solo contiene letras
}

int user_filter(char user[]){
    for (int i = 0; user[i] != '\0'; i++) {
        while (!isalpha(user[i])) {
            printf("El elemnto \"%c\", no es valido como parte del nombre de una Ciudad\n", user[i]);
            return 0;
        }

        /*
        if(strcmp(user, name) == 0 ){
            printf("Notcie that your provate user name and public user anme, are the same");
        }
         */
    }
    return 1;  // La cadena solo contiene letras
}

int city_filter(char city[]){
    if (!isupper(city[0])) {
        printf("La primera letra debe ser una mayuscula");
        return 0;  // La primera letra no es mayúscula
    }

    for (int i = 0; city[i] != '\0'; i++) {
        if (!isalpha(city[i])) {
            printf("caracter invalido: \"%c\"", city[i]);
            return 0;  // El nombre de la ciudad contiene un carácter que no es una letra
        }
    }

    return 1;  // El nombre de la ciudad es válido
}



int mail_filter(char mail[]){
    int longitud = (int) strlen(mail);
    int tieneArroba = 0;
    int tienePuntoDespuesArroba = 0;

    // Verificar que hay al menos un carácter antes y después de '@'
    for (int i = 0; i < longitud; i++) {
        if (mail[i] == '@') {
            tieneArroba = 1;
            if (i < longitud - 1)
                tienePuntoDespuesArroba = 1;
        }
    }

    // Verificar el formato general de la dirección de correo electrónico
    if (longitud > 2 && tieneArroba && tienePuntoDespuesArroba) {
        // Verificar que el primer y último carácter no sean '@' o '.'
        if (mail[0] != '@' && mail[0] != '.' && mail[longitud - 1] != '@' && mail[longitud - 1] != '.') {
            // Verificar que no haya dos o más caracteres '@' o '.'
            for (int i = 1; i < longitud - 1; i++) {
                if ((mail[i] == '@' && mail[i + 1] == '@') || (mail[i] == '.' && mail[i + 1] == '.')) {
                    return 0;
                }
            }
            return 1;  // La dirección de correo electrónico es válida
        }
    }
    printf("Direccio de correu electronica no valida\n");
    return 0;  // La dirección de correo electrónico no es válida
}

