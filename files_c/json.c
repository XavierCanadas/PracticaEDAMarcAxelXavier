#include "../files_h/json.h"

JsonObject* initJsonObject() {
    JsonObject *jsonObject = malloc(sizeof(JsonObject));
    memset(jsonObject->clau, 0, sizeof(jsonObject->clau));
    jsonObject->valor = NULL;
    jsonObject->type = jsonNull;

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

    JsonObject *result = initJsonObject();
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
    JsonObject *result = initJsonObject();
    int count = 0;
    int posicioInicial = 0;
    int caracterMirat = 0;
    int bracket_count = 0;
    int brace_count = 0;
    char *start = array->valor;
    printf("\n %s\n", start);
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

    char* input = (char*) malloc(sizeof(char)*(caracterMirat-posicioInicial + 1));
    strncpy(input, start + posicioInicial, caracterMirat);
    findValue(input, result, true);
    free(input);

    return result;
}
JsonObject* get_element_string_at_index(JsonObject *array, int index) {
    JsonObject* elementArray = initJsonObject();
    int count = 0;
    int posicioInicial = 0;
    int caracterMirat = 0;
    int contadorCometes = 0;
    bool cometesObertes = false;
    bool trobat = false;
    char *start = array->valor;
    printf("\n %s\n", start);
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
                break;
            } else {
                posicioInicial = caracterMirat + 1;
            }
        }

        if (index == count && contadorCometes == 0) {
            trobat = true;
            break;
        }
        caracterMirat++;

    }
    char* input = (char*) malloc(sizeof(char)*(caracterMirat-posicioInicial + 1));
    strncpy(input, start + posicioInicial + 1, caracterMirat-posicioInicial);
    elementArray->valor = input;
    if (trobat == true)
        elementArray->type = jsonString;
    else
        elementArray->type = jsonNull;

    return elementArray;

}
