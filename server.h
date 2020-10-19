#ifndef SERVER_H
#define SERVER_H

#include "common_socket.h"
#include "common_encoder_handler.h"
#include "common_input_output_handler.h"

/************************* Definicion de tipos de datos **********************/

typedef struct {
	socket_t self_socket;
    socket_t accept_socket;
	encoder_handler_t encoder;
}server_t;

/*************************** Declaración de primitivas de Client *************/

// Es la función que se encarga de iniciar la ejecución de un servidor, el 
// cual escuchará en el host y puerto que se hayan 
// indicado y luego recibirá un mensaje de un cliente el cual está codificado,
// luego lo decodificará, utilizando el método y la clave indicadas por
// parámetro, finalmente mostrará el mensaje por salida estándar.
// Pre: recibe un hostname, puerto, métod de cifrado y clave válidos.
// Post: devuelve 0 al finalizar la ejecución.
int serverRun(const char *port, const char *method, const char *key);

// Crea y ejecuta un servidor que escucha en el host y puerto indicado
// Pre: recibe un puntero a server_t, una dirección de host, un puerto
// un método de cifrado y una clave válida que utilizará el método
// Post: devuelve -1 en caso de error o 0 en caso de éxito.
int serverStart(server_t *server, 
				const char *port, const char *method, const char *key);

// Acepta un cliente, que se encuentra en espera por conectarse,
// estableciendo un canal de comunicación entre ellos.
// Pre: recibe un puntero a un server_t válido
// Post: el servidor acepta un cliente y establece el canal de
// comunicación devolviendo 0 en caso de éxito o -1 en caso de error.
int serverAccept(server_t *server);

// Recibe un mensaje cifrado de un cliente al cual está conectado
// Pre: recibe un puntero a un servidor creado
// Post: devuelve -1 en caso de error o 0 en caso de éxito.
int serverReceiveMessage(server_t *self);

// Finaliza la ejecución del servidor ordenadamente
// Pre: recibe un puntero un servidor creado
// Post: se destruyó el servidor y se liberaron los recursos utilizados
void serverFinish(server_t *self);

#endif //SERVER_H
