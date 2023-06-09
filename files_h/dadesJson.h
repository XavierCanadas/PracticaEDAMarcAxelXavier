//Includes
#include "../files_h/cola.h"
#include "../files_h/json.h"

// Fucions Json - Usuaris
JsonObject* llegirFitxer(char* direccioFitxer);
int llegirUsuarisJson(TaulaHash* taulaHash, JsonObject* root);
Usuari* convertirJsonUsuari(JsonObject* usuariJson);