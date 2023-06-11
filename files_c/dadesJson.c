//Includes
#include "../files_h/dadesJson.h"


/**
 * Es passa la direcció del fitxer json que conté totes les dades. La funció l'obre, agafa totes les dades i les posa
 * en un jsonObject del tipus jsonRoot.
 * @param direccioFitxer
 * @return
 */
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

/**
 * La funció recorre tot el jsonObject root, el desserialitza i guarda les dades dels usuaris a la taulaHash.
 * @param taulaHash
 * @param root
 * @param arrayPublciacions
 * @return
 */
int llegirUsuarisJson(TaulaHash* taulaHash, JsonObject* root, ArrayPublciacions* arrayPublciacions) {
    int nombreTotalUsuaris;

    // Es comproba que s'hagi passat l'arrel
    if (root->type != jsonRoot)
        return ERROR_JSON;

    // Comprova si la taula no està inicialitzada
    if (taulaHash == NULL || taulaHash->elements == NULL)
        return TAULA_NO_INICIALITZADA;

    JsonObject* arrayUsuaris = findInObject("usuaris", root);
    int midaArray = count_elements(arrayUsuaris);

    // s'itera per l'array d'usuaris i s'extreuen les dades de cada element.
    for (int i = 0; i < midaArray; ++i) {
        JsonObject* usuariJson = getElementAtIndex(arrayUsuaris, i);
        Usuari* aux = convertirJsonUsuari(usuariJson, arrayPublciacions);
        guardarUsuari(aux, aux->nomUsuari, taulaHash, NULL);
        borrarJsonObject(usuariJson);
    }
    return SUCCESS;
}
/**
 * Donat un usuari en forma de jsonObject, es mira les dades que el componen i crea un objetce Usuari
 * @param usuariJson
 * @param arrayPublciacions
 * @return
 */
Usuari* convertirJsonUsuari(JsonObject* usuariJson, ArrayPublciacions* arrayPublciacions) {
    // Es comprova si l'usuariJson passat és null
    if (usuariJson->type == jsonNull)
        return NULL;

    Usuari* usuari = initUsuari(); // s'inicialitza un usuari.

    // Agafa les variables que té un usuari en forma de JsonObject.
    JsonObject* nom = findInObject("nom", usuariJson);
    JsonObject* nomUsuari = findInObject("nomUsuari", usuariJson);
    JsonObject* correu = findInObject("correu", usuariJson);
    JsonObject* ciutat = findInObject("ciutat", usuariJson);
    JsonObject* edat = findInObject("edat", usuariJson);


    // Agafar l'array d'amics
    JsonObject* gustosArray = findInObject("gustos", usuariJson);
    JsonObject* unGust;

    // Agafar l'array d'amics
    JsonObject* amicsArray = findInObject("amics", usuariJson);
    JsonObject* unAmic;

    // Agafar l'array de solicituts
    JsonObject* solicituts = findInObject("solicituts", usuariJson);
    JsonObject* unaSolicitut;

    // Agafar l'array de publicació
    JsonObject* publicacions = findInObject("publicacions", usuariJson);



    // es copia cada variable de l'usuari.
    strcpy(usuari->nom, nom->valor);
    strcpy(usuari->nomUsuari, nomUsuari->valor);
    usuari->edat =  (int) strtol(edat->valor, NULL, 10);
    strcpy(usuari->correu, correu->valor);
    strcpy(usuari->ciutat, ciutat->valor);


    // es comprova si l'array de gustos és null i si no ho és itera per l'array i guarda els gustos.
    if (gustosArray->type != jsonNull) {
        for (int i = 0; i < (int) count_elements(gustosArray); ++i) {
            unGust = getElementStringAtIndex(gustosArray, i);
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
            unAmic = getElementStringAtIndex(amicsArray, i);
            guardarUsuari(NULL, unAmic->valor, usuari->amics, NULL);
            borrarJsonObject(unAmic);
        }
    }

    // s'agafen les solicituts pendents i es posen a la cua
    if (solicituts->type != jsonNull && solicituts->valor[0] != '\0') {
        int midaArray = (int) count_elements(solicituts);
        for (int i = 0; i < midaArray; ++i) {
            unaSolicitut = getElementStringAtIndex(solicituts, i);
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
/**
 * Donat una publicació en forma de jsonObject, es mira les dades que el componen i es guarda a l'array de publicacions
 * l'usuari i al general
 * @param publicacions
 * @param usuari
 * @param arrayPublciacions
 */
void convertirPublicacioJson(JsonObject* publicacions, Usuari* usuari, ArrayPublciacions* arrayPublciacions) {
    JsonObject* unaPublicacio;
    if (publicacions->type != jsonNull) {
        for (int i = 0; i < count_elements(publicacions); ++i) {
            unaPublicacio = getElementAtIndex(publicacions, i);
            JsonObject* contingut = findInObject("contingut", unaPublicacio);
            JsonObject* data = findInObject("data", unaPublicacio);
            JsonObject* likes = findInObject("likes", unaPublicacio);

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
/**
 * s'itera per la taula hash i es guarden els usuaris en un array jsonObject.
 * @param taulaHash
 * @return
 */
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
/**
 * Es converteix un usuari a un JsonObject, és la funció inversa de convertirJsonUsuari().
 * @param usuari
 * @return
 */
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

    // es copien els valors de l'usuari i es posen al jsonObject
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

    // es llibera de memòria tots els objectes auxiliars creats.
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

/**
 * es passa la llista d'amics d'un usuari i es converteix en un array en una sola string per poder-lo guaradr
 * en un jsonObject.
 * @param taulaHash
 * @return
 */
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

/**
 * es passa la llista de gustos d'un usuari i es converteix en un array en una sola string per poder-lo guaradr
 * en un jsonObject.
 * @param arrayGustos
 * @return
 */
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

/**
 * es passa un usuari, s'itera per la llista de publicacions i es converteix en un array en una sola string per poder-lo guaradr
 * en un jsonObject.
 * @param usuari
 * @return
 */
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


/**
 * Es passa una publicació i es converteix en un jsonObject.
 * @param publicacio
 * @return
 */
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

/**
 * es passa un usuari, s'itera per la cua de solicituts (fent dequeue) i es converteix en un array en una sola string per poder-lo guaradr
 * en un jsonObject.
 * @param usuari
 * @param nombreSolicituts
 * @return
 */
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
