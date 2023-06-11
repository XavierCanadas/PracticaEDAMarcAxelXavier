#include "../files_h/usuari.h"

// Menu opcions
#define VEURE_MEVES_PUB 1
#define VEURE_TOTES_PUB 2
#define TENDENCIES 3
#define SORTIR_PUB 4

ArrayPublciacions* initArrayPublicacions(int mida);
int ampliarArrayPublicacions(int novaMida, ArrayPublciacions* arrayPublciacions);
void freeArrayPublicacions(ArrayPublciacions* arrayPublciacions);

ArrayTendencies* initArrayTendencies(int mida);
int ampliarArraytendencies(int novaMida, ArrayTendencies* arrayTendencies);
void freeArrayTendencies(ArrayTendencies * arrayTendencies);
int hashingTendencies(ArrayTendencies* arrayTendencies, Tendencia* tendencia);
void afegirTendencies(Publicacio* publicacio, ArrayTendencies* arrayTendencies, ArrayTendencies* arrayTendenciesSorting);
void agafarTendenciesvoid(ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendencies, ArrayTendencies* arrayTendenciesSorting);
// Funció per realitzar una publicació
int realitzarPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendencies,ArrayTendencies* arrayTendenciesSorting);
void afegirPublicacio(Usuari* usuari, ArrayPublciacions* arrayPublciacions, char* contingut, char* data, int likes, ArrayTendencies* arrayTendencies,ArrayTendencies* arrayTendenciesSorting);

// Funció per mostrar les publicacions d'un usuari
;
void mostrarPublicacions(ArrayPublciacions* arrayPublciacions, Usuari* usuari, ArrayTendencies* arrayTendencies, ArrayTendencies* arrayTendenciesSorting);

void imprimirTendenciesFinal(ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendenciesSorting);