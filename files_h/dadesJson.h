//Includes
#include "../files_h/cola.h"
#include "../files_h/json.h"

// Fucions Json - Usuaris
JsonObject* llegirFitxer(char* direccioFitxer);
int llegirUsuarisJson(TaulaHash* taulaHash, JsonObject* root);
Usuari* convertirJsonUsuari(JsonObject* usuariJson);
JsonObject* usuariAJson(Usuari* usuari);
char** convertirArrayAmics_arrayString(TaulaHash* taulaHash);
char** convertirArrayGustos(char arrayGustos[5][MAX_STRING]);
JsonObject* guardarUsuarisJson(TaulaHash* taulaHash);