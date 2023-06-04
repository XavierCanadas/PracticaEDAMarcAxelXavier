#include "../files_h/usuari.h"

/// Opcions del menú
#define ENVIAR_SOLICITUD 1
#define ACEPTAR_SOLICITUD 2
#define REBUTJAR_SOLICITUD 3
#define SORTIR_GESTIONAR_SOLICITUTS 4

///funcions
void inicializarCola(ColaSolicitudes* cola);
bool colaVacia(ColaSolicitudes* cola);
void encolar(ColaSolicitudes* cola, const char* remitente, const char* destinatario);
void desencolar(ColaSolicitudes* cola);
void rechazarSolicitud(ColaSolicitudes* cola);
void gestionSolicitudesAmistad(Usuari* usuari);
void acceptarSolicitud(ColaSolicitudes* cola, Usuari* usuari);