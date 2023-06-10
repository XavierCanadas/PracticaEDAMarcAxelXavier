//Includes
#include "../files_h/publicacions.h"

// Opcions del menú
#define ENVIAR_SOLICITUD 1
#define ACEPTAR_SOLICITUD 2
#define REBUTJAR_SOLICITUD 3
#define SORTIR_GESTIONAR_SOLICITUTS 4

//funcions
void inicializarCola(ColaSolicitudes** cola);
bool colaVacia(ColaSolicitudes* cola);
void encolar(ColaSolicitudes* cola, const char* remitente, const char* destinatario);
void desencolar(ColaSolicitudes* cola);
int longitudCola(ColaSolicitudes* cola);
void rechazarSolicitud(ColaSolicitudes* cola);
void gestionSolicitudesAmistad(Usuari* usuari,TaulaHash* taula);
void acceptarSolicitud(ColaSolicitudes* cola, Usuari* usuari, TaulaHash* taulaHash);