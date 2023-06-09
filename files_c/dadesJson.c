//Includes
#include "../files_h/dadesJson.h"


/// Llegir dades
JsonObject* llegirFitxer(char* direccioFitxer) {
    int mida;
    FILE* file = fopen(direccioFitxer, "r");
    JsonObject* jsonObject = (JsonObject*) malloc(sizeof(JsonObject));

    if (file) {
        fseek(file, 0, SEEK_END);
        mida = ftell(file);
        fseek(file, 0, SEEK_SET);
        jsonObject->valor = (char*) malloc(mida);
        if (jsonObject->valor) {
            fread(jsonObject->valor, 1, mida, file);
        }
        fclose(file);
    }
    memset(jsonObject->clau, 0, sizeof(jsonObject->clau));
    jsonObject->type = jsonRoot;



    return jsonObject;
}

int llegirUsuarisJson(TaulaHash* taulaHash, JsonObject* root) {
    int nombreTotalUsuaris;

    // Es comproba que s'hagi passat l'arrel
    if (root->type != jsonRoot)
        return ERROR_JSON;

    // Comprova si la taula no està inicialitzada
    if (taulaHash == NULL || taulaHash->elements == NULL)
        return TAULA_NO_INICIALITZADA;

    JsonObject* arrayUsuaris = find_in_object("usuaris", root);
    int midaArray = count_elements(arrayUsuaris);

    for (int i = 0; i < midaArray; ++i) {
        JsonObject* usuariJson = get_element_at_index(arrayUsuaris, i);
        Usuari* aux = convertirJsonUsuari(usuariJson);
        guardarUsuari(aux, aux->nomUsuari, taulaHash, NULL);
        borrarJsonObject(usuariJson);
    }

    return SUCCESS;
}

Usuari* convertirJsonUsuari(JsonObject* usuariJson) {
    // Es comprova si l'usuariJson passat és null
    if (usuariJson->type == jsonNull)
        return NULL;

    Usuari* usuari = initUsuari(); // s'inicialitza un usuari.

    JsonObject* nom = find_in_object("nom", usuariJson);
    JsonObject* nomUsuari = find_in_object("nomUsuari", usuariJson);
    JsonObject* correu = find_in_object("correu", usuariJson);
    JsonObject* ciutat = find_in_object("ciutat", usuariJson);
    JsonObject* edat = find_in_object("edat", usuariJson);


    // Agafar l'array d'amics
    JsonObject* gustosArray = find_in_object("gustos", usuariJson);
    JsonObject* unGust;

    // Agafar l'array d'amics
    JsonObject* amicsArray = find_in_object("amics", usuariJson);
    JsonObject* unAmic;

    // es copia cada variable de l'usuari.
    strcpy(usuari->nom, nom->valor);
    strcpy(usuari->nomUsuari, nomUsuari->valor);
    usuari->edat =  (int) strtol(edat->valor, NULL, 10);
    strcpy(usuari->correu, correu->valor);
    strcpy(usuari->ciutat, ciutat->valor);


    // es comprova si l'array de gustos és null i si no ho és itera per l'array i guarda els gustos.
    if (gustosArray->type != jsonNull) {
        for (int i = 0; i < (int) count_elements(gustosArray); ++i) {
            unGust = get_element_string_at_index(gustosArray, i);
            strcpy(usuari->gustos[i], unGust->valor);
            borrarJsonObject(unGust);
        }

    }
    // inicialitza la taulaHash per guardar els amics.
    initTaulaHash(usuari->amics, 10);

    // es guarden els amics.
    if (amicsArray->type != jsonNull && amicsArray->valor[0] != '\0') {
        int midaArray = (int) count_elements(amicsArray);
        for (int i = 0; i < midaArray; ++i) {
            unAmic = get_element_string_at_index(amicsArray, i);
            guardarUsuari(NULL, unAmic->valor, usuari->amics, NULL);
            borrarJsonObject(unAmic);
        }

    }
    // Lliberar de memòria tot.
    borrarJsonObject(nom);
    borrarJsonObject(nomUsuari);
    borrarJsonObject(edat);
    borrarJsonObject(correu);
    borrarJsonObject(ciutat);
    borrarJsonObject(amicsArray);
    borrarJsonObject(gustosArray);

    return usuari;
}

/// Escriure dades
JsonObject* guardarUsuarisJson(TaulaHash* taulaHash) {
    JsonObject* arrayUsuarisJson = initJsonObject("usuaris", "", jsonArray);
    char** arrayAux = (char**) calloc(taulaHash->count, sizeof(char*));
    int midaArray = 0, comptador = 0;
    bool esFinal = false;

    for (int i = 0; i < taulaHash->size; ++i) {
        if (taulaHash->elements[i].valor != NULL) {
            if (taulaHash->elements[i].valor != NULL) {
                if (comptador == taulaHash->count - 1)
                    esFinal = true;
                arrayAux[comptador] = jsonObjectToString(usuariAJson(taulaHash->elements[i].valor),false,esFinal);
                midaArray += (int) strlen(arrayAux[comptador]);
                comptador++;
            }
        }
    }
    arrayUsuarisJson->valor = (char*) calloc(midaArray+1, sizeof(char));
    for (int i = 0; i < comptador; ++i) {
        strcat(arrayUsuarisJson->valor, arrayAux[i]);
        free(arrayAux[i]);
    }
    free(arrayAux);
    return arrayUsuarisJson;
}

JsonObject* usuariAJson(Usuari* usuari) {
    JsonObject* usuariJson = initJsonObject(NULL, NULL, jsonTypeObjet);
    int midaStringUsuari = 0;

    // Comproba si és null el punter passat.
    if (usuari == NULL) {
        return NULL;
    }

    // Afegir els components de l'usuari
    JsonObject* nom = initJsonObject("nom", usuari->nom, jsonString);
    midaStringUsuari += jsonObjectStringLength(nom, true);

    JsonObject* nomUsuari = initJsonObject("nomUsuari", usuari->nomUsuari, jsonString);
    midaStringUsuari += jsonObjectStringLength(nomUsuari, true);

    // Convertir l'edat a un string i posar-ho a un jsonObject
    char edatString[3];
    sprintf(edatString, "%d", usuari->edat);
    JsonObject* edat = initJsonObject("edat", edatString, jsonInt);
    midaStringUsuari += jsonObjectStringLength(edat, true);

    JsonObject* correu = initJsonObject("correu", usuari->correu, jsonString);
    midaStringUsuari += jsonObjectStringLength(correu, true);

    JsonObject* ciutat = initJsonObject("ciutat", usuari->ciutat, jsonString);
    midaStringUsuari += jsonObjectStringLength(ciutat, true);

    // array gustos i amics

    char* arrayGustos = arrayToString(convertirArrayGustos(usuari->gustos), 5);
    JsonObject* gustos = initJsonObject("gustos", arrayGustos, jsonArray);
    midaStringUsuari += jsonObjectStringLength(gustos, true);

    char* arrayAmics = arrayToString(convertirArrayAmics_arrayString(usuari->amics), usuari->amics->count);
    JsonObject* amics = initJsonObject("amics", arrayAmics, jsonArray);
    midaStringUsuari += jsonObjectStringLength(amics, true);


    usuariJson->valor = (char*) calloc(midaStringUsuari + 1, sizeof(char));
    strcat(usuariJson->valor, jsonObjectToString(nom, true, false));
    strcat(usuariJson->valor, jsonObjectToString(nomUsuari, true, false));
    strcat(usuariJson->valor, jsonObjectToString(edat, true, false));
    strcat(usuariJson->valor, jsonObjectToString(correu, true, false));
    strcat(usuariJson->valor, jsonObjectToString(ciutat, true, false));
    strcat(usuariJson->valor, jsonObjectToString(gustos, true, false));
    strcat(usuariJson->valor, jsonObjectToString(amics, true, true));

    borrarJsonObject(nom);
    borrarJsonObject(nomUsuari);
    borrarJsonObject(edat);
    borrarJsonObject(correu);
    borrarJsonObject(ciutat);
    borrarJsonObject(gustos);
    borrarJsonObject(amics);

    return usuariJson;
}

char** convertirArrayAmics_arrayString(TaulaHash* taulaHash) {
    int comptador = 0;
    char** arrayAmics = (char**) calloc(taulaHash->count, sizeof(char*));
    for (int i = 0; i < taulaHash->size; ++i) {
        if (taulaHash->elements[i].clau[0] != '\0') {
            arrayAmics[comptador] = (char*) calloc(strlen(taulaHash->elements[i].clau), sizeof(char));
            strcpy(arrayAmics[comptador], taulaHash->elements[i].clau);
            comptador++;
        }
    }
    return arrayAmics;
}

char** convertirArrayGustos(char arrayGustos[5][MAX_STRING]) {
    char** array = (char**) calloc(5, sizeof(char*));
    int comtador = 0;
    for (int i = 0; i < 5; ++i) {
        if (strcmp(arrayGustos[i], "") != 0) {
            char* string = (char*) calloc(strlen(arrayGustos[i]+1), sizeof(char));
            strcpy(string, arrayGustos[i]);
            strcat(string, "\0");
            array[comtador] = string;
            comtador++;
        }
    }
    return array;
}

