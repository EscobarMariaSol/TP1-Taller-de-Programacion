#include "server.h"

#define LEN_METHOD 9
#define LEN_KEY 6
#define BUFFER_TAM 64

/************************Funciones Auxiliares*********************************/

array_t *ReceiveMessage(socket_t *socket) {
    int recv = 0;
    unsigned char buffer[BUFFER_TAM] = {0};
    array_t *recv_msg = arrayCreate(0);
    if (!recv_msg) return NULL;
    do {
		if((recv = socketRecv(socket, buffer, BUFFER_TAM)) == -1) break;
		if (arrayAdd(recv_msg, buffer, recv) < 0) {
			arrayDestroy(recv_msg);
			return NULL;
		}
		memset(buffer, 0, BUFFER_TAM);	
	} while (recv > 0);
    return recv_msg;
}

int showMessage(array_t *message) {
    io_handler_t io_handler;
    if (ioHandlerCreate(&io_handler, NULL)) return -1;
    int resp = ioHandlerSetMessage(&io_handler, message);
    ioHandlerDestroy(&io_handler);
    return resp;
}

/************************Primitivas del TDA Server****************************/

int serverRun(const char *port, const char *method, const char *key) {
    server_t server;
    if (serverStart(&server, port, method, key) < 0)
        return -1;
    if ((serverAccept(&server) < 0) || (serverReceiveMessage(&server) < 0)) {
        serverFinish(&server);
        return -1;
    }
    serverFinish(&server);
    return 0;
}

int serverStart(server_t *server, const char *port, 
                    const char *method, const char *key) {
    memset(server, 0, sizeof(server_t));
    if (socketCreate(&server->self_socket, NULL, port, 1)) return -1;
    if (encoderHandlerCreate(&server->encoder, 
                            (&method[LEN_METHOD]), 
                            (char *)(&key[LEN_KEY]))) {
        socketDestroy(&server->self_socket);
        return -1;
    }
    return 0;
}

int serverAccept(server_t *self) {
    return socketAccept(&self->self_socket, &self->accept_socket);
}

int serverReceiveMessage(server_t *self) {
    array_t *message, *encodedMessage;
    if (!(encodedMessage = ReceiveMessage(&self->accept_socket))) return -1;
    if (!(message= encoderHandlerDecode(&self->encoder, encodedMessage))) {
        arrayDestroy(encodedMessage);
        return -1;
    }
    arrayDestroy(encodedMessage);
    int resp = showMessage(message);
    arrayDestroy(message);
    return resp;
}

void serverFinish(server_t *self) {
    socketDestroy(&self->self_socket);
    if (&self->accept_socket) 
        socketDestroy(&self->accept_socket);
    encoderHandlerDestroy(&self->encoder);
}
