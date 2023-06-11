//Includes
#include "../global.h"
#include "../files_h/dadesJson.h"


// Opcions del menú
#define NOU_USUARI 1
#define LLISTA_USUARIS 2
#define ESCOLLIR_USUARI 3
#define MOSTRAR_OPCIONS 4
#define SORTIR 5

// Opcions sub-menu (Menu Usuari)
#define GESTIONAR_SOLICITUTS 1
#define FER_PUBLICACIO 2
#define VEURE_PUBLICACIONS 3
#define ELIMINAR_USUARI 4
#define SORTIR_MENU_USUARI 5

// Funcions:
int bucleMenu();
void showMenuOptions();

void showEscollirUsuaruMenu(Usuari *usuari);
int bucleEscollirUsuari(TaulaHash* taula, ArrayPublciacions* arrayPublciacions, ArrayTendencies* arrayTendencies, ArrayTendencies* arrayTendenciesSorting);


