#include "../files_h/cola.h"
#include "../files_h/json.h"

JsonObject* llegirFitxer(char* direccioFitxer);
int llegirUsuarisJson(TaulaHash* taulaHash, JsonObject* root);
Usuari* convertirJsonUsuari(JsonObject* usuariJson);
JsonObject* usuariAJson(Usuari* usuari);
JsonObject* guardarUsuarisJson(TaulaHash* taulaHash);

char** convertirArrayAmics_arrayString(TaulaHash* taulaHash);
char** convertirArrayGustos(char arrayGustos[5][MAX_STRING]);
char** convertirArrayPublicacions(Usuari* usuari);
JsonObject* publicacioAJson(Publicacio* publicacio);
char** convertirSolicitutsJson(Usuari* usuari);