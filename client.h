#ifndef CLIENT_H
#define CLIENT_H

#include "common_socket.h"
#include "common_encoder_handler.h"
#include "common_input_output_handler.h"

/************************* Definicion de tipos de datos **********************/

typedef struct {
	socket_t socket;
	encoder_handler_t encoder;
}client_t;

/*************************** Declaración de primitivas de Client *************/

// Inicia la ejecución de un cliente, el cual se conectará al host y puerto
// indicados yluego enviará un mensaje codificado utilizando el método y la
// clave indicadas por parámetro.
// Pre: recibe un hostname, puerto, métod de cifrado y clave válidos.
// Post: devuelve 0 al finalizar la ejecución.
int clientRun(const char *host, const char *port, 
				const char *method, const char *key);

// Devuelve un cliente conectado al host y puerto indicado
// Pre: recibe un puntero a client_t, una dirección de host, un puerto
// un método de cifrado y la clave para cifrar
// Post: devuelve -1 en caso de error o 0 en caso de éxito.
int clientStart(client_t *client, const char *host, 
				const char *port, const char *method, const char *key);

// Envia un mensaje al servidor al cuál está conectado el cliente 
// El mensaje a enviar se recibe por entrada estádar
// Pre: recibe un puntero a un cliente creado
// Post: devuelve -1 en caso de error o 0 en caso de éxito.
int clientSendMessage(client_t *self);

// Finaliza la ejecución del cliente
// Pre: recibe un puntero un cliente creado
// Post: se destruyó el cliente y se liberaron los recursos utilizados
void clientFinish(client_t *self);

#endif //CLIENT_H
