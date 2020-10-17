#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

/*******Definición de tipos de datos********/

typedef struct {
	uint16_t fd;
}socket_t;

/*******Primitivas de socket*******/

// Crea un nuevo socket conectado a al host y puerto especificados
// Pre: Recibe un puntero a socket_t, un nombre de host, un puerto
// y el tipo de socket, 0 para cliente y 1 para server
// Post: devuleve -1 en caso de error o 0 en caso de éxito
int socketCreate(socket_t* socket, const char* host, 
					const char* port, uint16_t type);

// Crea el socket aceptador en representación de la conexión establecida
// Pre: Recibe un puntero al socket conectado y otro a un nuevo socket
// que funcionará como canal de comunicación
// Post: devuleve -1 en caso de error o 0 en caso de éxito
int socketAccept(socket_t* self, socket_t* accept_socket);

// Envia mensajes de un socket a otro
// Pre: Recibe un puntero a socket_t, un buffer y la
// cantidad de bytes a recibir
// Post: devuleve -1 en caso de error o 0 en caso de éxito
int socketSend(socket_t* self, const unsigned char* buffer, size_t size);

// Recive un mensaje desde otro socket y lo almacena en el buffer
// Pre: Recibe un puntero a socket_t, un buffer y la
// cantidad de bytes a enviar
// Post: devuleve -1 en caso de error o 0 en caso de éxito
int socketRecv(socket_t* self, unsigned char *buffer, size_t size);

// Destruye el socket
// Pre: recibe un socket que fue creado
// Post: el socket fue destruido y los recursos utilizados fueron liberados
void socketDestroy(socket_t* self);

#endif // COMMON_SOCKET_H
