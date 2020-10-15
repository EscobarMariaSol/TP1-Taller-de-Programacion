#include "client.h"

#define LEN_METHOD 9
#define LEN_KEY 6

/************************Funciones Auxiliares*********************************/

array_t *getMessage(void) {
    input_output_handler_t io_handler;
    if (inputOutputHandlerCreate(&io_handler, NULL)) return NULL;
    array_t *message = inputOutputHandlerGetMessage(&io_handler);
    inputOutputHandlerDestroy(&io_handler);
    return message;
}

int sendMessage(socket_t *socket, array_t *message) {
    int sent = 0, total_sent = 0;
    unsigned char *buffer = arrayGetContent(message);
    if (!buffer) return -1;
	do {
        sent = socketSend(socket, buffer, arrayGetSize(message) - total_sent);
		if (sent < 0) return -1;
		buffer = buffer + sent;
		total_sent += sent;
	} while ((sent > 0) && (total_sent < arrayGetSize(message)));
	return 0;
}

/************************Primitivas del TDA Client****************************/

int clientStart(client_t *client, const char *host, const char *port, const char *method, const char *key) {
    memset(client, 0, sizeof(client_t));
    if (socketCreate(&client->socket, host, port, 0)) return -1;
    if (encoderHandlerCreate(&client->encoder, (&method[LEN_METHOD]), (char *)(&key[LEN_KEY]))) {
        socketDestroy(&client->socket);
        return -1;
    }
    return 0;
}

int clientSendMessage(client_t *self) {
    array_t *message, *encodedMessage;
    if (!(message = getMessage())) return -1;
    if (!(encodedMessage = encoderHandlerEncode(&self->encoder, message))) {
        arrayDestroy(message);
        return -1;
    }
    arrayDestroy(message);
    int answer = sendMessage(&self->socket, encodedMessage);
    arrayDestroy(encodedMessage);
    return answer;
}

void clientFinish(client_t *self) {
    socketDestroy(&self->socket);
    encoderHandlerDestroy(&self->encoder);
}