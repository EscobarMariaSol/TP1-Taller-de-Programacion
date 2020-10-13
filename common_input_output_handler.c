#include "common_input_output_handler.h"

#define BUFFER_TAM 64

/************************Primitivas del file handler****************/

int inputOutputHandlerCreate(input_output_handler_t *handler, const char *path) {
    memset(handler, 0, sizeof(input_output_handler_t));
    FILE *new_file;
    if (path) {
		if ((new_file = fopen(path,"r")) == NULL ) return -1;
	} else {
		new_file = stdin;
	}
    handler->file = new_file;
    return 0;
}

array_t *inputOutputHandlerGetContent(input_output_handler_t * self) {
	int  buff_len;
    array_t *contenido = arrayCreate(BUFFER_TAM);
    if (!contenido) return NULL;
	char buffer[BUFFER_TAM] = {'\0'};
	while (fgets(buffer, BUFFER_TAM, self->file)) {
		buff_len = strlen(buffer);
		if(arrayAdd(contenido, buffer, buff_len) < 0) return NULL;
	}	
	return contenido;
}

int inputOutputHandlerSetContent(input_output_handler_t * self, array_t *message) {
	char *text = arrayGetContent(message);
	if (!text) return -1;
	if (self->file == stdin) self->file = stdout;
	return (fwrite(text, 1, arrayGetSize(message), self->file));
}

void inputOutputHandlerDestroy(input_output_handler_t * self) {
    if((self->file != stdin) && (self->file != stdout)) 
		fclose(self->file);
}