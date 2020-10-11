#ifndef COMMON_FILE_HANDLER_H
#define COMMON_FILE_HANDLER_H

#include "common_array.h"

typedef struct {
    FILE *file;
}file_handler_t;

// Crea un nuevo manejador de archivo
int fileHandlerCreate(file_handler_t *file_handler, const char *path);

// Devuleve el contenido del archivo
array_t *fileHandlerGetFileContent(file_handler_t * self);

// Destruye el manejador de archivo que se le pasa por parámetro
void fileHandlerDestroy(file_handler_t * self);

#endif //COMMON_FILE_HANDLER_H