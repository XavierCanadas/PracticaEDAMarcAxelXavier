#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


typedef enum  {
    jsonString,
    jsonInt,
    jsonArray,
    jsonNull,
    jsonTypeObjet,
    jsonRoot
}JsonTypes;

typedef struct jsonObject{
    char clau[50];
    char* valor;
    JsonTypes type;
}JsonObject;

JsonObject* initJsonObject(char* clau, char* valor, JsonTypes jsonTypes);
void borrarJsonObject(JsonObject* jsonObject);

// Lectura
void findValue(char *input, JsonObject *object, bool objectInArray);
void handleObject(char *start, JsonObject *object);
void handleArray(char *start, JsonObject *object);
void handleString(char *start, JsonObject *object);
JsonObject* findInObject(char *key, JsonObject *object);
int count_elements(JsonObject *object);
JsonObject* getElementAtIndex(JsonObject *array, int index);
JsonObject* getElementStringAtIndex(JsonObject *array, int index);

// Escriptura
char* jsonObjectToString(JsonObject *object, bool clau, bool esFinal, bool esRoot);
int jsonObjectStringLength(JsonObject *object, bool clau);
char* arrayToString(char* array[], int size);
void freeArrayStringsDinamic(char** array);