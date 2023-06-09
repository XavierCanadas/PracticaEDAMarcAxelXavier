#include "../files_h/json.h"

JsonObject* initJsonObject(char* clau, char* valor, JsonTypes jsonTypes) {
    JsonObject *jsonObject = calloc(1,sizeof(JsonObject));
    if (clau != NULL)
        strcpy(jsonObject->clau, clau);

    if (valor != NULL) {
        jsonObject->valor = (char*) calloc(strlen(valor + 1), sizeof(char));
        strcpy(jsonObject->valor, valor);
    }


    jsonObject->type = jsonTypes;

    return jsonObject;
}

void borrarJsonObject(JsonObject* jsonObject) {
    if (jsonObject != NULL) {
        free(jsonObject->valor);
        memset(jsonObject->clau, 0, sizeof(jsonObject->clau));
        free(jsonObject);
        jsonObject = NULL;
    }
}

void findKey(char *input, JsonObject *object) {
    char *start, *end;
    start = strchr(input, '\"');
    if (start != NULL) {
        end = strchr(start + 1, '\"');
        if (end != NULL) {
            strncpy(object->clau, start + 1, end - start - 1);
            object->clau[end - start - 1] = '\0';
        }
    }
}

void handle_string(char *start, JsonObject *object) {
    char *end;
    end = strchr(start + 1, '\"');
    if (end != NULL) {
        object->valor = malloc(end - start);
        strncpy(object->valor, start + 1, end - start - 1);
        object->valor[end - start - 1] = '\0';
        object->type = jsonString;
    }
}

void handle_array(char *start, JsonObject *object) {
    int count = 1;
    char *end = start + 1;
    while (*end != '\0' && count > 0) {
        if (*end == '[') count++;
        else if (*end == ']') count--;
        end++;
    }
    if (count == 0) {
        end--;
        object->valor = malloc(end - start);
        strncpy(object->valor, start + 1, end - start - 1);
        object->valor[end - start - 1] = '\0';
        object->type = jsonArray;
    }
}

void handle_object(char *start, JsonObject *object) {
    char *end;
    end = strchr(start + 1, '}');
    if (end != NULL) {
        object->valor = malloc(end - start + 2);
        strncpy(object->valor, start + 1, end - start - 1);
        object->valor[end - start] = '\0';
        object->type = jsonTypeObjet;
    }
}

void findValue(char *input, JsonObject *object, bool objectInArray) {
    char *start;
    if (objectInArray == true) {
        start = input;
    } else {
        start = strchr(input, ':');
    }

    if (start != NULL) {
        if (objectInArray == false)
            start++;
        while (isspace(*start)) start++;
        if (*start == '\"') {
            handle_string(start, object);
        } else if (*start == '[') {
            handle_array(start, object);
        } else if (*start == '{') {
            handle_object(start, object);
        } else if (isdigit(*start) || *start == '-') {
            char *end;
            end = start;
            while (isdigit(*end) || *end == '-') end++;
            object->valor = malloc(end - start + 1);
            strncpy(object->valor, start, end - start);
            object->valor[end - start] = '\0';
            object->type = jsonInt;
        } else {
            object->valor = malloc(1);
            object->valor[0] = '\0';
            object->type = jsonNull;
        }
    }
}

JsonObject* find_in_object(char *key, JsonObject *object) {
    JsonObject *result = initJsonObject(NULL, NULL, jsonNull);
    char *start = strstr(object->valor, key);
    if (start != NULL) {
        strncpy(result->clau, key, strlen(key));
        result->clau[strlen(key)] = '\0';
        findValue(start - 1 , result, false);
    }

    return result;
}

void splitString(char *input, JsonObject *object) {
    findKey(input, object);
    findValue(input, object, false);
}

int count_elements(JsonObject *object) {
    int count = 0;
    int bracket_count = 0;
    int brace_count = 0;
    char *start = object->valor;
    while (*start != '\0') {
        if (*start == '[') bracket_count++;
        else if (*start == ']') bracket_count--;
        else if (*start == '{') brace_count++;
        else if (*start == '}') brace_count--;
        else if (*start == ',' && bracket_count == 0 && brace_count == 0) count++;
        start++;
    }
    return count + 1;
}


JsonObject* get_element_at_index(JsonObject *array, int index) {
    JsonObject *result = initJsonObject(NULL, NULL, jsonNull);
    int count = 0;
    int posicioInicial = 0;
    int caracterMirat = 0;
    int bracket_count = 0;
    int brace_count = 0;
    char *start = array->valor;
    result->clau[0] = '\0';
    while (start[caracterMirat] != '\0') {
        if (start[caracterMirat] == '[') bracket_count++;
        else if (start[caracterMirat] == ']') bracket_count--;
        else if (start[caracterMirat] == '{') brace_count++;
        else if (start[caracterMirat] == '}') brace_count--;
        else if (start[caracterMirat] == ',' && bracket_count == 0 && brace_count == 0) {
            //posicioInicial = caracterMirat + 1;
            count++;

            if (count == (index + 1)) {
                break;
            } else {
                posicioInicial = caracterMirat + 1;
            }

        }  else if (bracket_count == 0 && brace_count == 0 && count == index) {
            break;
        }
        caracterMirat++;
    }

    if (start[caracterMirat] == '\0') caracterMirat--;

    char* input = (char*) malloc(sizeof(char)*(caracterMirat-posicioInicial+4));
    strncpy(input, start + posicioInicial, caracterMirat - posicioInicial + 2);
    findValue(input, result, true);

    free(input);

    return result;
}
JsonObject* get_element_string_at_index(JsonObject *array, int index) {
    JsonObject* elementArray = initJsonObject(NULL, NULL, jsonNull);
    int count = 0;
    int posicioInicial = 0;
    int caracterMirat = 0;
    int contadorCometes = 0;
    bool cometesObertes = false;
    bool trobat = false;
    char *start = array->valor;
    elementArray->clau[0] = '\0';

    while (start[caracterMirat] != '\0') {
        if (start[caracterMirat] == '"') {
            if (cometesObertes == false) {
                contadorCometes++;
                cometesObertes = true;
            } else{
                contadorCometes--;
                cometesObertes = false;
            }

        } else if (start[caracterMirat] == ',' && contadorCometes == 0) {
            count++;

            if (count == (index + 1)) {
                trobat = true;
                caracterMirat--;
                break;
            } else {
                posicioInicial = caracterMirat + 1;
            }
        }

        if (index == count && contadorCometes == 0 && index == 0) {
            trobat = true;
            break;
        }
        caracterMirat++;

    }

    if (start[caracterMirat] == '\0') caracterMirat--;

    char* input = (char*) calloc((caracterMirat-posicioInicial - 1), sizeof(char));
    strncpy(input, start + posicioInicial + 1, caracterMirat-posicioInicial - 1);
    elementArray->valor = input;
    if (trobat == true)
        elementArray->type = jsonString;
    else
        elementArray->type = jsonNull;

    return elementArray;

}

char* jsonObjectToString(JsonObject *object, bool clau, bool esFinal) {
    char* output = (char*) calloc(jsonObjectStringLength(object, clau) + 2, sizeof(char));

    // El problema està aquí, revisar
    if (clau == true && object->type != (jsonRoot) && object->type != (jsonTypeObjet)) {
        strcat(output, "\"");
        strcat(output, object->clau);
        strcat(output, "\":");
    }

    switch (object->type) {
        case jsonString:
            strcat(output, "\"");
            strcat(output, object->valor);
            strcat(output, "\"");
            break;
        case jsonInt:
            strcat(output, object->valor);
            break;
        case jsonArray:
            strcat(output, "[");

            strcat(output, object->valor);
            strcat(output, "]");
            break;
        case jsonNull:
            strcat(output, "null");
            break;
        case jsonTypeObjet:
        case jsonRoot:
            strcat(output, "{");
            // El problema està aquí, revisar
            if (clau == true) {
                strcat(output, "\"");
                strcat(output, object->clau);
                strcat(output, "\":");
            }
            strcat(output, object->valor);
            strcat(output, "}");
            break;
    }
    if (esFinal == true)
        strcat(output, "\0"); // S'afegeix el caràcter final
    else
        strcat(output, ",");

    return output;
}

int jsonObjectStringLength(JsonObject *object, bool clau) {
    int length = 0;

    if (clau == true)
        length += (int) strlen(object->clau) + 4; // for the key and quotes

    switch (object->type) {
        case jsonInt:
            length += (int) strlen(object->valor);
            break;
        case jsonString:
        case jsonArray:
        case jsonTypeObjet:
        case jsonRoot:
            length += (int) strlen(object->valor) + 2;
            break;
        case jsonNull:
            break;
    }
    return length;
}

char* arrayToString(char** array, int size) {
    int total_size = 3, contador = 0; // es té en compte els [] i el caràcter nul.
    for (int i = 0; i < size; i++) {
        if (array[i] != NULL && strcmp(array[i], "\0") != 0)
            total_size += (int) strlen(array[i]) + 4;
    }
    char* result = (char*) calloc(total_size + 1, sizeof(char));

    for (int i = 0; i < size; i++) {
        if (array[i] != NULL && strcmp(array[i], "\0") != 0) {
            strcat(result, "\"");
            strcat(result, array[i]);
            strcat(result, "\"");

            /// Cambiar: s'ha de modificar pq funcioni bé per guardar els amics.
            if (i != size - 1 && array[i+1] != NULL) {
                strcat(result, ",");
            }

            free(array[i]);
            array[i] = NULL;
        }
    }
    //strcat(result, "\0");

    free(array);

    //freeArrayStringsDinamic(array);

    return result;
}

void freeArrayStringsDinamic(char** array) {
    int i = 0;
    if (array != NULL) {
        while (array[i] != NULL) {
            free(array[i]);
            i++;
        }
        free(array);
    }
}