/*
 Aquest Header servirà per definir constants globals que serveixin per a tot el programa com els valors booleans,
 tipus d'errors generals… Així no s'hauran de declarar en cada header.
 */

// Importar llibreries per tot el programa
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

// Declaració de constants globals
#define SUCCESS 33 // Per saber si una funció ha tingut èxit.
#define OPCIO_INVALIDA (-10)
#define ERROR_ENTRADA_DADES 0 // la funció scanf retorna 0 si no s'ha introduït el que demana
#define MAX_STRING 50
#define CONFIRMAR 1
#define CANCELAR 0
#define TAULA_NO_INICIALITZADA (-1)
#define ERROR_JSON (-2)



// Funcions globals
int entradaInt(char missatge[]);
int entradaString(char missatge[], char entradaUsuari[], char filtres[]);
int scan(char entradaUsuari[]);
void flush_input();





#ifndef UNTITLED2_GLOBAL_H
#define UNTITLED2_GLOBAL_H
#endif //UNTITLED2_GLOBAL_H
