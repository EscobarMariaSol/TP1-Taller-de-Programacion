#ifndef COMMON_INPUT_OUTPUT_HANDLER_H
#define COMMON_INPUT_OUTPUT_HANDLER_H

#include "common_array.h"

typedef struct {
    FILE *file;
}input_output_handler_t;

// Crea un nuevo manejador de archivo
int inputOutputHandlerCreate(input_output_handler_t *handler, const char *path);

// Devuleve el contenido de entrada
array_t *inputOutputHandlerGetContent(input_output_handler_t * self);

// Setea  el contenido de salida
int inputOutputHandlerSetContent(input_output_handler_t * self, array_t *message);

// Destruye el manejador de archivo que se le pasa por parámetro
void inputOutputHandlerDestroy(input_output_handler_t * self);

#endif //COMMON_INPUT_OUTPUT_HANDLER_H