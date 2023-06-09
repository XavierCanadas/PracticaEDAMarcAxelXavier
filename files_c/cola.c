//Includes
#include "../files_h/cola.h"

//Inicialitza la cua de sol·licituds.
void inicializarCola(ColaSolicitudes* cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

/*
 Comprova si la cua de sol·licituds està buida.
 Retorna true si la cua està buida, false en cas contrari.
 */
bool colaVacia(ColaSolicitudes* cola) {
    return cola->frente == NULL;
}


//Afegeix una nova sol·licitud de amistat a la cua.
void encolar(ColaSolicitudes* cola, const char* remitente, const char* destinatario) {
    NodoSolicitud* nuevoNodo = (NodoSolicitud*)malloc(sizeof(NodoSolicitud));
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

    printf("Sol·licitud d'amistat enviada a %s.\n", destinatario);
}


//Elimina la sol·licitud de amistat del davant de la cua.
void desencolar(ColaSolicitudes* cola) {
    if (colaVacia(cola)) {
        printf("La cua de sol.licituds esta buida.\n");
        return;
    }

    NodoSolicitud* nodoEliminar = cola->frente;
    printf("Solalicitud d'amistat de %s acceptada.\n", nodoEliminar->remitente);

    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoEliminar);
}


//Rebutja la sol·licitud de amistat del davant de la cua.
void rechazarSolicitud(ColaSolicitudes* cola) {
    if (colaVacia(cola)) {
        printf("La cua de solalicituds esta buida.\n");
        return;
    }

    NodoSolicitud* nodoEliminar = cola->frente;
    printf("Sol.licitud d'amistat de %s rebutjada.\n", nodoEliminar->remitente);

    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodoEliminar);
}

/*
 Accepta la sol·licitud d'amistat del davant de la cua.
 Afegeix l'amistat a la llista d'amics de l'usuari.
*/
void acceptarSolicitud(ColaSolicitudes* cola, Usuari* usuari) {
    if (colaVacia(cola)) {
        printf("No hi han solicituts damistad pendents.\n");
        return;
    }
    NodoSolicitud* nodoAceptar = cola->frente;
    printf("Aceptant solicituds d'amistad de %s...\n", nodoAceptar->remitente);

    // Agregar remitente como amigo
    int indexAmic;



    int resultado = guardarUsuari(NULL, nodoAceptar->remitente, usuari->amics, NULL);
    if (resultado == SUCCESS) {
        printf("Solicitud d'amistad acceptada. %s ara es el teu amigo.\n", nodoAceptar->remitente);
    } else {
        printf("Error al aceptar solicitud d'amistad.\n");
    }
    desencolar(cola);
    free(nodoAceptar);
}



/*
 Gestiona les sol·licituds d'amistat.
 Proporciona un menú per enviar, acceptar o rebutjar sol·licituds de amistat.
*/
void gestionSolicitudesAmistad(Usuari* usuari) {
    ColaSolicitudes cola; //Todo ??
    inicializarCola(&cola);
    int opcion = 0;
    while (opcion != SORTIR_GESTIONAR_SOLICITUTS) {
        printf("\n----- GESTIO DE SOL.LICITUDS D'AMISTAT -----\n");
        printf("%d. Enviar sol.licitud d'amistat\n", ENVIAR_SOLICITUD);
        printf("%d. Acceptar sol.licitud d'amistat\n", ACEPTAR_SOLICITUD);
        printf("%d. Rebutjar sol.licitud d'amistat\n", REBUTJAR_SOLICITUD);
        printf("%d. Sortir\n", SORTIR_GESTIONAR_SOLICITUTS);
        opcion = entradaInt("Introdueix el numero de l'opcio desitjada: ");

        switch (opcion) {
            case ENVIAR_SOLICITUD: {
                //char remitente[MAX_STRING] = usuari->nomUsuari;
                char remitente[MAX_STRING];
                char destinatario[MAX_STRING];
                // No té sentit que es demani l'emissor pq es passa com a paràmetre a la funció.
                entradaString("Introdueix el nom d'usuari de l'emissor: ", remitente, "user");
                entradaString("Introdueix el nom d'usuari del destinatari: ", destinatario, "user");

                // s'hauria de passar com a remitent el nom d'usuari de l'objecte usuari del paràmetre
                if(strcmp(remitente,destinatario)!=0) encolar(&cola, remitente, destinatario);
                else printf("Error al enviar la sol·licitud");
                break;
            }
            case ACEPTAR_SOLICITUD:
                acceptarSolicitud(&cola, usuari);
                break;
            case REBUTJAR_SOLICITUD:
                rechazarSolicitud(&cola);
                break;
            case SORTIR_GESTIONAR_SOLICITUTS:
                printf("Surt del programa...\n");
                break;
            default:
                printf("Opcio invalida. Si us plau, introdueix un numero valid.\n");
                break;
        }

        printf("---------------------------------------------\n\n");
    }
}
