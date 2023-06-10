#include "../files_h/usuari.h"

// Menu opcions
#define VEURE_MEVES_PUB 1
#define VEURE_TOTES_PUB 2
#define TENDENCIES 3
#define SORTIR_PUB 4

ArrayPublciacions* initArrayPublicacions(int mida);
int ampliarArrayPublicacions(int novaMida, ArrayPublciacions* arrayPublciacions);
void freeArrayPublicacions(ArrayPublciacions* arrayPublciacions);

// Funció per realitzar una publicació
int realitzarPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions);
void afegirPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions, char* contingut, char* data, int likes);

// Funció per mostrar les publicacions d'un usuari
;
void mostrarPublicacions(ArrayPublciacions* arrayPublciacions, Usuari* usuari);

