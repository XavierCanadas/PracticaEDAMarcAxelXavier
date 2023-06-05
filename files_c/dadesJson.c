#include "../files_h/dadesJson.h"

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
    // iniccialitza la taulaHash per guardar els amics.
    initTaulaHash(usuari->amics, 10);

    // es guarden els amics.
    if (amicsArray->type != jsonNull) {
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