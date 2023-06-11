#include "../files_h/json.h"

/** Descripció
 *  Es reserva espai a memòria per un JsonObject i se li assignen els valors passats pels paràmetres.
 *
 * @param clau: la clau del nou objecte, pot ser nul.
 * @param valor: el valor del nou objecte, pot ser nul.
 * @param jsonTypes: indica el tipus d'objecte que és.
 * @return retorna un objecte jsonObject inicialitzat.
 */
JsonObject* initJsonObject(char* clau, char* valor, JsonTypes jsonTypes) {
    JsonObject *jsonObject = calloc(1,sizeof(JsonObject));
    if (clau != NULL)
        strcpy(jsonObject->clau, clau);

    if (valor != NULL) {
        jsonObject->valor = (char*) calloc(strlen(valor) + 5, sizeof(char));
        strcpy(jsonObject->valor, valor);
    }
    jsonObject->type = jsonTypes;

    return jsonObject;
}

/** Descripció:
 *  Es llibera de la memòria l'espai que ocupa el jsonObject passat com a paràmetre.
 * @param jsonObject: ha d'estar inicialitzat.
 */
void borrarJsonObject(JsonObject* jsonObject) {
    if (jsonObject != NULL) {
        free(jsonObject->valor);
        memset(jsonObject->clau, 0, sizeof(jsonObject->clau));
        free(jsonObject);
        jsonObject = NULL;
    }
}

/// Funcions per desserialitzar els JsonObjects

/** Descripció:
 *  Es passa una string que contingui un JsonObject, la funció itera per la string i identifica quin tipus d'objecte és, després extrau el valor
 *  i l'assigna a l'objecte passat com a paràmetre.
 *
 * @param input: una string que conté el jsonObject per convertir
 * @param jsonObject: un jsonObject inicialitzat que se li assignaran els valors de la string.
 * @param objectInArray: si el jsonObject que hi ha a la string és del tipus JsonTypeObject que està dintre d'un array, aquest booleà ha de ser true.
 */
void findValue(char* input, JsonObject* jsonObject, bool objectInArray) {
    char* start;

    if (objectInArray == true) {
        start =input;
    } else {
        start = strchr(input, ':');
    }

    if (start != NULL) {
        if (objectInArray == false)
            start++;
        while (isspace(*start)) start++;
        if (*start == '\"') {
            handleString(start, jsonObject);
        } else if (*start == '[') {
            handleArray(start, jsonObject);
        } else if (*start == '{') {
            handleObject(start, jsonObject);
        } else if (isdigit(*start) || *start == '-') {
            char *end;
            end = start;
            while (*end != '\0' && isdigit(*end)) {
                end++;
            }
            jsonObject->valor = calloc(1,end - start + 1);
            strncpy(jsonObject->valor, start, end - start);
            jsonObject->valor[end - start] = '\0';
            jsonObject->type = jsonInt;
        } else {
            jsonObject->valor = calloc(1,1);
            jsonObject->valor[0] = '\0';
            jsonObject->type = jsonNull;
        }
    }
}

/** Descripció:
 *  Si l'objecte passat a findValue() del tipus jsonString, es crida aquesta funció. La seva finalitat
 *  és extreure el valor i asignar-lo al jsonObject
 *
 * @param start
 * @param jsonObject
 */
void handleString(char* start, JsonObject* jsonObject) {
    char* end;
    end = strchr(start + 1, '\"');
    if (end != NULL) {
        jsonObject->valor = calloc(1,end - start);
        strncpy(jsonObject->valor, start + 1, end - start - 1);
        jsonObject->valor[end - start - 1] = '\0';
        jsonObject->type = jsonString;
    }
}
/** Descripció:
 *  Si l'objecte passat a findValue() del tipus jsonArray, es crida aquesta funció. La seva finalitat
 *  és extreure el valor i asignar-lo al jsonObject.
 *
 * @param start
 * @param jsonObject
 */
void handleArray(char* start, JsonObject* jsonObject) {
    int count = 1; // serveix per identificar els '[' i']' que hi ha, quan sigui 0 significarà que l'array ha acabat.
    char* end = start + 1;
    while (*end != '\0' && count > 0) {
        if (*end == '[') count++;
        else if (*end == ']') count--;
        end++;
    }
    if (count == 0) {
        end--;
        jsonObject->valor = calloc(1,end - start + 2);
        strncpy(jsonObject->valor, start + 1, end - start - 1);
        jsonObject->valor[end - start - 1] = '\0';
        jsonObject->type = jsonArray;
    }
}

/** Descripció:
 *  Si l'objecte passat a findValue() del tipus jsonTypeObjet, es crida aquesta funció. La seva finalitat
 *  és extreure el valor i asignar-lo al jsonObject.
 * @param start
 * @param jsonObject
 */
void handleObject(char* start, JsonObject* jsonObject) {
    char* end = start + 1;
    int count = 1;
    while (*end != '\0' && count > 0) {
        if (*end == '{') count++;
        else if (*end == '}') count--;
        end++;
    }

    if (count == 0 && end != NULL) {
        jsonObject->valor = calloc(1,end - start + 4);
        strncpy(jsonObject->valor, start + 1, end - start - 1);
        jsonObject->valor[end - start] = '\0';
        jsonObject->type = jsonTypeObjet;
    }
}

/** Descripció:
 *  Es passa una clau i un jsonObject, es busca la clau dintre del valor del jsonObject i s'agafa l'objecte que té la clau.
 * @param key
 * @param jsonObject
 * @return es retorna un nou jsonObject amb la clau passada i l'objecte que li correspon.
 */
JsonObject* findInObject(char *key, JsonObject* jsonObject) {
    JsonObject* result = initJsonObject(NULL, NULL, jsonNull);
    char* start = strstr(jsonObject->valor, key);
    if (start != NULL) {
        strncpy(result->clau, key, strlen(key));
        result->clau[strlen(key)] = '\0';
        findValue(start - 1 , result, false);
    }
    strcat(result->valor, "\0");

    return result;
}
/** Descripció
 *  es passa un jsonObject que conté un array, la funció compte els elements que hi ha a l'array.
 * @param jsonObject
 * @return
 */
int count_elements(JsonObject* jsonObject) {
    int count = 0;
    int bracket_count = 0;
    int brace_count = 0;
    char* start = jsonObject->valor;
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

// linear search
/** Descripció:
 *  La funció itera per cada element del jsonArray passat i retorna l'objecte que hi ha a l'índex passat.
 *  Es fa servir l'estrategia de linear search per trobar l'element. Per poder trobar-lo hi ha diferents comtadors que
 *  controlen els '[]´, '{}' i ',' que hi ha per poder comptar els elements.
 * @param array
 * @param index
 * @return
 */
JsonObject* getElementAtIndex(JsonObject* array, int index) {
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

    char* input = (char*) calloc((caracterMirat-posicioInicial+4),sizeof(char));
    strncpy(input, start + posicioInicial, caracterMirat - posicioInicial + 2);
    findValue(input, result, true);

    free(input);

    return result;
}
/** Descripció:
 *  Recorre un array de stirng json i retorna el valor que hi ha a l'índex passat. Ho hem dividit respecte a l'anterior
 *  perquè hi havia errors inesperats.
 * @param array
 * @param index
 * @return
 */
JsonObject* getElementStringAtIndex(JsonObject *array, int index) {
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

/// Funcions per serialitzar els jsonObjects

/** Descripció:
 *  Converteix un JsonObject a una string dinàmica, hi ha diferents boleans com a paràmetre que serveixen per especificar el
 *  tipus de string que es vol.
 * @param object
 * @param clau
 * @param esFinal
 * @param esRoot
 * @return
 */
char* jsonObjectToString(JsonObject* jsonObject, bool clau, bool esFinal, bool esRoot) {
    // es guarda espai de més per seguretat.
    char* output = (char*) calloc(jsonObjectStringLength(jsonObject, clau) + 10, sizeof(char));

    if (esRoot == true) {
        strcat(output, "{");
    }

    // El problema està aquí, revisar
    if (clau == true && jsonObject->type != (jsonRoot) && jsonObject->type != (jsonTypeObjet)) {
        strcat(output, "\"");
        strcat(output, jsonObject->clau);
        strcat(output, "\":");
    }

    switch (jsonObject->type) {
        case jsonString:
            strcat(output, "\"");
            strcat(output, jsonObject->valor);
            strcat(output, "\"");
            break;
        case jsonInt:
            strcat(output, jsonObject->valor);
            break;
        case jsonArray:
            strcat(output, "[");

            strcat(output, jsonObject->valor);
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
                strcat(output, jsonObject->clau);
                strcat(output, "\":");
            }
            strcat(output, jsonObject->valor);
            strcat(output, "}");
            break;
    }
    if (esRoot == true) {
        strcat(output, "}");
    }
    if (esFinal == true)
        strcat(output, "\0"); // S'afegeix el caràcter final
    else
        strcat(output, ",");

    return output;
}
/**
 * Donat un jsonObject i un booleà, es calcula la llargària que tindrà l'objecte com a string.
 * @param object
 * @param clau
 * @return
 */
int jsonObjectStringLength(JsonObject* jsonObject, bool clau) {
    int length = 0;

    if (clau == true)
        length += (int) strlen(jsonObject->clau) + 4; // for the key and quotes

    switch (jsonObject->type) {
        case jsonInt:
            length += (int) strlen(jsonObject->valor);
            break;
        case jsonString:
        case jsonArray:
        case jsonTypeObjet:
        case jsonRoot:
            length += (int) strlen(jsonObject->valor) + 2;
            break;
        case jsonNull:
            break;
    }
    return length;
}
/**
 * Es converteix un array de strings a una sola string.
 * @param array
 * @param size
 * @return
 */
char* arrayToString(char** array, int size) {
    int total_size = 3, contador = 0; // es té en compte els [] i el caràcter nul.
    for (int i = 0; i < size; i++) {
        if (array[i] != NULL && strcmp(array[i], "\0") != 0)
            total_size += (int) strlen(array[i]) + 4;
    }
    char* result = (char*) calloc(total_size + 2, sizeof(char));

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

    free(array);
    return result;
}