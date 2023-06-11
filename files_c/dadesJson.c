//Includes
#include "../files_h/dadesJson.h"


// Llegir dades
JsonObject* llegirFitxer(char* direccioFitxer) {
    long mida;
    FILE* file = fopen(direccioFitxer, "r");
    JsonObject* jsonObject = initJsonObject(NULL, NULL, jsonRoot);

    if (file) {
        fseek(file, 0, SEEK_END);
        mida =  ftell(file) + 2;
        fseek(file, 0, SEEK_SET);
        jsonObject->valor = (char*) calloc(1, mida);
        if (jsonObject->valor) {
            fread(jsonObject->valor, 1, mida - 2, file);
        }
        fclose(file);
    }

    return jsonObject;
}

int llegirUsuarisJson(TaulaHash* taulaHash, JsonObject* root, ArrayPublciacions* arrayPublciacions) {
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
        Usuari* aux = convertirJsonUsuari(usuariJson, arrayPublciacions);
        guardarUsuari(aux, aux->nomUsuari, taulaHash, NULL);
        borrarJsonObject(usuariJson);
    }

    return SUCCESS;
}

Usuari* convertirJsonUsuari(JsonObject* usuariJson, ArrayPublciacions* arrayPublciacions) {
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

    // Agafar l'array de solicituts
    JsonObject* solicituts = find_in_object("solicituts", usuariJson);
    JsonObject* unaSolicitut;

    // Agafar l'array de publicació
    JsonObject* publicacions = find_in_object("publicacions", usuariJson);



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
    // iniccialitza la taulaHash per guardar els amics.
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

    // s'agafen les solicituts pendents i es posen a la cua
    if (solicituts->type != jsonNull && solicituts->valor[0] != '\0') {
        int midaArray = (int) count_elements(solicituts);
        for (int i = 0; i < midaArray; ++i) {
            unaSolicitut = get_element_string_at_index(solicituts, i);
            encolar(usuari->solicitudsAmistat, unaSolicitut->valor, usuari->nomUsuari);
            borrarJsonObject(unaSolicitut);
        }
    }

    // s'afegeixen les publicacions
    if (publicacions->type != jsonNull && publicacions->valor[0] != '\0')
        convertirPublicacioJson(publicacions, usuari, arrayPublciacions);

    // Lliberar de memòria tot.
    borrarJsonObject(nom);
    borrarJsonObject(nomUsuari);
    borrarJsonObject(edat);
    borrarJsonObject(correu);
    borrarJsonObject(ciutat);
    borrarJsonObject(amicsArray);
    borrarJsonObject(gustosArray);
    borrarJsonObject(solicituts);
    borrarJsonObject(publicacions);

    return usuari;
}
void convertirPublicacioJson(JsonObject* publicacions, Usuari* usuari, ArrayPublciacions* arrayPublciacions) {
    JsonObject* unaPublicacio;
    if (publicacions->type != jsonNull) {
        for (int i = 0; i < count_elements(publicacions); ++i) {
            unaPublicacio = get_element_at_index(publicacions, i);
            JsonObject* contingut = find_in_object("contingut", unaPublicacio);
            JsonObject* data = find_in_object("data", unaPublicacio);
            JsonObject* likes = find_in_object("likes", unaPublicacio);

            // S'afegeix la publicació a l'array de l'usuari i també al que les conté totes.
            afegirPublicacio(usuari, arrayPublciacions, contingut->valor, data->valor, (int) strtol(likes->valor, NULL, 10), NULL, NULL);

            // Es llibera de memòria els objectes creats
            borrarJsonObject(contingut);
            borrarJsonObject(data);
            borrarJsonObject(likes);
            borrarJsonObject(unaPublicacio);

        }
    }

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
                arrayAux[comptador] = jsonObjectToString(usuariAJson(taulaHash->elements[i].valor),false,esFinal, false);
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

    // Nom
    JsonObject* nom = initJsonObject("nom", usuari->nom, jsonString);
    midaStringUsuari += jsonObjectStringLength(nom, true);

    // Nom d'usuari
    JsonObject* nomUsuari = initJsonObject("nomUsuari", usuari->nomUsuari, jsonString);
    midaStringUsuari += jsonObjectStringLength(nomUsuari, true);

    // Convertir l'edat a un string i posar-ho a un jsonObject
    char edatString[3];
    sprintf(edatString, "%d", usuari->edat);
    JsonObject* edat = initJsonObject("edat", edatString, jsonInt);
    midaStringUsuari += jsonObjectStringLength(edat, true);

    // Correu
    JsonObject* correu = initJsonObject("correu", usuari->correu, jsonString);
    midaStringUsuari += jsonObjectStringLength(correu, true);

    // Ciutat
    JsonObject* ciutat = initJsonObject("ciutat", usuari->ciutat, jsonString);
    midaStringUsuari += jsonObjectStringLength(ciutat, true);

    // Gustos
    char* arrayGustos = arrayToString(convertirArrayGustos(usuari->gustos), 5);
    JsonObject* gustos = initJsonObject("gustos", arrayGustos, jsonArray);
    midaStringUsuari += jsonObjectStringLength(gustos, true);

    // Amics
    char* arrayAmics = arrayToString(convertirArrayAmics_arrayString(usuari->amics), usuari->amics->count);
    JsonObject* amics = initJsonObject("amics", arrayAmics, jsonArray);
    midaStringUsuari += jsonObjectStringLength(amics, true);

    // Solicituts d'amistat
    int nombreSolicituts = longitudCola(usuari->solicitudsAmistat);
    char* arraySolicituts = arrayToString(convertirSolicitutsJson(usuari, nombreSolicituts), nombreSolicituts);
    JsonObject* solicituts = initJsonObject("solicituts", arraySolicituts, jsonArray);
    midaStringUsuari += jsonObjectStringLength(solicituts, true);

    // Publicacions
    JsonObject* publicacions = arrayPublicacionsJson(usuari);
    midaStringUsuari += jsonObjectStringLength(publicacions, true);

    // Nombre de publicacions
    char nombrePublicacionsString[10];
    sprintf(nombrePublicacionsString, "%d", usuari->nombrePublicacions);
    JsonObject* nombrePublicacions = initJsonObject("nPublicacions", nombrePublicacionsString, jsonInt);
    midaStringUsuari += jsonObjectStringLength(nombrePublicacions, true);

    usuariJson->valor = (char*) calloc(midaStringUsuari + 1, sizeof(char));
    strcat(usuariJson->valor, jsonObjectToString(nom, true, false, false));
    strcat(usuariJson->valor, jsonObjectToString(nomUsuari, true, false, false));
    strcat(usuariJson->valor, jsonObjectToString(edat, true, false, false));
    strcat(usuariJson->valor, jsonObjectToString(correu, true, false, false));
    strcat(usuariJson->valor, jsonObjectToString(ciutat, true, false, false));
    strcat(usuariJson->valor, jsonObjectToString(gustos, true, false,false));
    strcat(usuariJson->valor, jsonObjectToString(amics, true, false, false));
    strcat(usuariJson->valor, jsonObjectToString(solicituts, true, false, false));
    strcat(usuariJson->valor, jsonObjectToString(publicacions, true, false,false));
    strcat(usuariJson->valor, jsonObjectToString(nombrePublicacions, true, true, false));


    borrarJsonObject(nom);
    borrarJsonObject(nomUsuari);
    borrarJsonObject(edat);
    borrarJsonObject(correu);
    borrarJsonObject(ciutat);
    borrarJsonObject(gustos);
    borrarJsonObject(amics);
    borrarJsonObject(solicituts);
    borrarJsonObject(publicacions);
    borrarJsonObject(nombrePublicacions);


    return usuariJson;
}

char** convertirArrayAmics_arrayString(TaulaHash* taulaHash) {
    int comptador = 0;
    char** arrayAmics = (char**) calloc(taulaHash->count, sizeof(char*));
    for (int i = 0; i < taulaHash->size; ++i) {
        if (taulaHash->elements[i].clau[0] != '\0') {
            arrayAmics[comptador] = (char*) calloc(strlen(taulaHash->elements[i].clau)+1, sizeof(char));
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
        if (arrayGustos[i][0] != '\0') {
            char* string = (char*) calloc(strlen(arrayGustos[i])+1, sizeof(char));
            strcpy(string, arrayGustos[i]);
            strcat(string, "\0");
            array[comtador] = string;
            comtador++;
        }
    }
    return array;
}

JsonObject* arrayPublicacionsJson(Usuari* usuari) {
    JsonObject* arrayPublicacions = initJsonObject("publicacions", NULL, jsonArray);
    char** arrayAux = (char**) calloc(usuari->nombrePublicacions, sizeof(char*));
    int midaArray = 0, comptador = 0;
    bool esFinal = false;

    for (int i = 0; i < usuari->nombrePublicacions; ++i) {
        JsonObject* publicacio = publicacioAJson(usuari->arrayPublciacions->publicacions[i]);
        if (publicacio != NULL){
            if (comptador == usuari->nombrePublicacions - 1)
                esFinal = true;
            arrayAux[comptador] = jsonObjectToString(publicacio, false, esFinal, false);
            midaArray += (int) strlen(arrayAux[comptador]);
            comptador++;
        }
    }
    arrayPublicacions->valor = (char*) calloc(midaArray + 5, sizeof(char));

    for (int i = 0; i < comptador; ++i) {
        strcat(arrayPublicacions->valor, arrayAux[i]);
        free(arrayAux[i]);
    }
    free(arrayAux);
    return arrayPublicacions;
}



JsonObject* publicacioAJson(Publicacio* publicacio) {
    JsonObject* publicacioJson = initJsonObject(NULL, NULL, jsonTypeObjet);
    int midaString = 0;

    if (publicacio == NULL)
        return NULL;

    // contingut
    JsonObject* contingut = initJsonObject("contingut", publicacio->contingut, jsonString);
    midaString += jsonObjectStringLength(contingut, true);

    // data
    JsonObject* data = initJsonObject("data", publicacio->data, jsonString);
    midaString += jsonObjectStringLength(data, true);

    // m'agrada
    char likesString[3];
    sprintf(likesString, "%d", publicacio->likes);
    JsonObject* likes = initJsonObject("likes", likesString, jsonInt);
    midaString += jsonObjectStringLength(likes, true);

    // S'afegeixen tots els jsonObject a PublicacioJson.
    publicacioJson->valor = (char*) calloc(midaString + 5, sizeof(char));
    strcat(publicacioJson->valor, jsonObjectToString(contingut, true, false, false));
    strcat(publicacioJson->valor, jsonObjectToString(data, true, false, false));
    strcat(publicacioJson->valor, jsonObjectToString(likes, true, true, false));

    // Es lliberen de memòria els JsonObject
    borrarJsonObject(contingut);
    borrarJsonObject(data);
    borrarJsonObject(likes);

    return publicacioJson;
}

char** convertirSolicitutsJson(Usuari* usuari, int nombreSolicituts) {
    NodoSolicitud* solicitut;
    char** array = (char**) calloc(nombreSolicituts + 1, sizeof(char*));
    int comptador = 0;

    while (colaVacia(usuari->solicitudsAmistat) == false) {
        solicitut = usuari->solicitudsAmistat->frente;
        if (solicitut->remitente[0] != '\0') {
            array[comptador] = (char*) calloc(strlen(solicitut->remitente)+1, sizeof(char));
            strcpy(array[comptador], solicitut->remitente);
            desencolar(usuari->solicitudsAmistat);
            comptador++;
        }
    }
    return array;
}
