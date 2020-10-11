#include "common_file_handler.h"

#define BUFFER_TAM 64

/************************Primitivas del file handler****************/

int fileHandlerCreate(file_handler_t *file_handler, const char *path) {
    memset(file_handler, 0, sizeof(file_handler_t));
    FILE *new_file;
    if (path) {
		if ((new_file = fopen(path,"r")) == NULL ) return -1;
	} else {
		new_file = stdin;
	}
    file_handler->file = new_file;
    return 0;
}

array_t *fileHandlerGetFileContent(file_handler_t * self) {
    array_t *contenido = arrayCreate(BUFFER_TAM);
    if (!contenido) return NULL;
	char buffer[BUFFER_TAM] = {'\0'};
	while (fgets(buffer, BUFFER_TAM, self->file)) {
		int  buff_len = strlen(buffer);
		if(arrayAdd(contenido, buffer, buff_len) < 0) return NULL;
	}	
	return contenido;
}

void fileHandlerDestroy(file_handler_t * self) {
    fclose(self->file);
}