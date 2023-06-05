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

JsonObject* initJsonObject();
void borrarJsonObject(JsonObject* jsonObject);
void findKey(char *input, JsonObject *object);
void findValue(char *input, JsonObject *object, bool objectInArray);
void splitString(char *input, JsonObject *object);
void handle_object(char *start, JsonObject *object);
void handle_array(char *start, JsonObject *object);
void handle_string(char *start, JsonObject *object);
JsonObject* find_in_object(char *key, JsonObject *object);
int count_elements(JsonObject *object);
JsonObject* get_element_at_index(JsonObject *array, int index);
JsonObject* get_element_string_at_index(JsonObject *array, int index);