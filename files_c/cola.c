//Includes
#include "../files_h/cola.h"

//Inicialitza la cua de sol·licituds.
void inicializarCola(ColaSolicitudes** cola) {
    *cola = (ColaSolicitudes*) calloc(1,sizeof(ColaSolicitudes));
    (*cola)->frente = NULL;
    (*cola)->final = NULL;
}

/*
 Comprova si la cua de sol·licituds està buida.
 Retorna true si la cua està buida, false en cas contrari.
 */
bool colaVacia(ColaSolicitudes* cola) {
    if (cola->frente == NULL) return true;
    return false;
}


//Afegeix una nova sol·licitud de amistat a la cua.
void encolar(ColaSolicitudes* cola, const char* remitente, const char* destinatario) {
    NodoSolicitud* nuevoNodo = (NodoSolicitud*)calloc(1,sizeof(NodoSolicitud));
    strcpy(nuevoNodo->remitente, remitente);
    strcpy(nuevoNodo->destinatario, destinatario);
    nuevoNodo->siguiente = NULL;

    if (colaVacia(cola)) {
        cola->frente = nuevoNodo;
        cola->final = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
        cola->final = nuevoNodo;
    }
}


//Elimina la sol·licitud d'amistat del davant de la cua.
void desencolar(ColaSolicitudes* cola) {
    if (cola->frente==NULL) return;
    NodoSolicitud* aux = cola->frente;
    cola->frente = cola->frente->siguiente;
    free(aux);
}

int longitudCola(ColaSolicitudes* cola) {
    int contador = 0;
    NodoSolicitud* aux = cola->frente;
    while (aux != NULL){
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

//Rebutja la sol·licitud d'amistat del davant de la cua.
void rechazarSolicitud(ColaSolicitudes* cola) {
    if (colaVacia(cola)==true) {
        printf("La cua de solalicituds esta buida.\n");
        return;
    }
    //eliminem la solicitud
    printf("Sol.licitud d'amistat de %s rebutjada.\n", cola->frente->remitente);

    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }
}

/*
 Accepta la sol·licitud d'amistat del davant de la cua.
 Afegeix l'amistat a la llista d'amics de l'usuari.
*/
void acceptarSolicitud(ColaSolicitudes* cola, Usuari* usuari) {
    if (colaVacia(cola)==true) {
        printf("No hi han solicituts d'amistat pendents.\n");
        return;
    }
    int resultado = guardarUsuari(NULL, cola->frente->remitente, usuari->amics, NULL);
    if (resultado == SUCCESS) {
        printf("Solicitud d'amistad acceptada, %s ara es el teu amic.\n", cola->frente->remitente);
    } else {
        printf("Error al aceptar solicitud d'amistat.\n");
    }
    desencolar(cola);
}



/*
 Gestiona les sol·licituds d'amistat.
 Proporciona un menú per enviar, acceptar o rebutjar sol·licituds de amistat.
*/
void gestionSolicitudesAmistad(Usuari* usuari,TaulaHash* taula) {
    usuari->solicitudsAmistat;
    int opcion = 0;
    while (opcion != SORTIR_GESTIONAR_SOLICITUTS) {
        printf("\n----- GESTIO DE SOL.LICITUDS D'AMISTAT -----\n");
        printf("\t %d. Enviar sol.licitud d'amistat\n", ENVIAR_SOLICITUD);
        printf("\t %d. Acceptar sol.licitud d'amistat\n", ACEPTAR_SOLICITUD);
        printf("\t %d. Rebutjar sol.licitud d'amistat\n", REBUTJAR_SOLICITUD);
        printf("\t %d. Sortir\n", SORTIR_GESTIONAR_SOLICITUTS);
        opcion = entradaInt("Introdueix el numero de l'opcio desitjada: ");

        switch (opcion) {
            case ENVIAR_SOLICITUD: {
                char destinatario[MAX_STRING];
                entradaString("Introdueix el nom d'usuari del destinatari: ", destinatario, "none");
                Usuari *user= buscarUsuari(taula, destinatario);
                // s'hauria de passar com a remitent el nom d'usuari de l'objecte usuari del paràmetre
                if(strcmp(usuari->nomUsuari,destinatario)!=0) encolar(user->solicitudsAmistat, usuari->nomUsuari, destinatario);
                else printf("Error al enviar la sol·licitud");
                printf("Sol·licitud d'amistat enviada a %s.\n", destinatario);
                break;
            }
            case ACEPTAR_SOLICITUD:
                acceptarSolicitud(usuari->solicitudsAmistat, usuari);
                break;
            case REBUTJAR_SOLICITUD:
                rechazarSolicitud(usuari->solicitudsAmistat);
                break;
            case SORTIR_GESTIONAR_SOLICITUTS:
                break;
            default:
                printf("Opcio invalida. Si us plau, introdueix un numero valid.\n");
                break;
        }

        printf("---------------------------------------------\n\n");
    }
}
