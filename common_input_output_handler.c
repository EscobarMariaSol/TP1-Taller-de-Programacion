#include "common_input_output_handler.h"

#define BUFFER_TAM 64

/************************Primitivas del file handler****************/

int ioHandlerCreate(io_handler_t *handler, const char *path) {
    memset(handler, 0, sizeof(io_handler_t));
    FILE *new_file;
    if (path) {
		if ((new_file = fopen(path,"r")) == NULL ) return -1;
	} else {
		new_file = stdin;
	}
    handler->file = new_file;
    return 0;
}

array_t *ioHandlerGetMessage(io_handler_t * self) {
    array_t *contenido = arrayCreate(0);
    if (!contenido) return NULL;
	char buffer[BUFFER_TAM] = {0};
	while (fgets(buffer, BUFFER_TAM, self->file)) {
		int buff_len = strlen(buffer);
		if(arrayAdd(contenido, (unsigned char*) buffer, buff_len) < 0)
			return NULL;
		memset(buffer, 0, BUFFER_TAM);
	}	
	return contenido;
}

int ioHandlerSetMessage(io_handler_t * self, array_t *message) {
	unsigned char *text = arrayGetContent(message);
	if (!text) return -1;
	if (self->file == stdin) self->file = stdout;
	return (fwrite(text, 1, arrayGetSize(message), self->file));
}

void ioHandlerDestroy(io_handler_t * self) {
    if ((self->file != stdin) && (self->file != stdout)) 
		fclose(self->file);
}
