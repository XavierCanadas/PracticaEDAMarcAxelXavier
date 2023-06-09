#include "../files_h/usuari.h"

ArrayPublciacions* initArrayPublicacions();
int ampliarArrayPublicacions(int novaMida, ArrayPublciacions* arrayPublciacions);
void freeArrayPublicacions(ArrayPublciacions* arrayPublciacions);

// Funció per realitzar una publicació
int realitzarPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions);

// Funció per mostrar les publicacions d'un usuari
;
void mostrarPublicacions(ArrayPublciacions* arrayPublciacions, Usuari* usuari);

