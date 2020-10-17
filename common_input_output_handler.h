#ifndef COMMON_INPUT_OUTPUT_HANDLER_H
#define COMMON_INPUT_OUTPUT_HANDLER_H

#include "common_array.h"

typedef struct {
    FILE *file;
}io_handler_t;

// Crea un nuevo manejador de archivo
int ioHandlerCreate(io_handler_t *handler, const char *path);

// Devuleve el contenido de entrada
array_t *ioHandlerGetMessage(io_handler_t * self);

// Setea  el contenido de salida
int ioHandlerSetMessage(io_handler_t * self, array_t *message);

// Destruye el manejador de archivo que se le pasa por parámetro
void ioHandlerDestroy(io_handler_t * self);

#endif //COMMON_INPUT_OUTPUT_HANDLER_H