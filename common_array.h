#ifndef COMMON_ARRAY_H
#define COMMON_ARRAY_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
    char *buffer;
    size_t size;
    uint32_t pos;
}array_t;

// Crea un arreglo 
array_t* arrayCreate(size_t size);

// Copia un mensaje al final del arreglo
int arrayAdd(array_t *self, const char *msg, size_t len);

// Limpia el contenido del arreglo
int arrayClear(array_t *self);

// Devuelve el contenido dentro del arreglo
char *arrayGetContent(array_t *self);

// Devuelve el largo del arreglo
size_t arrayGetSize(array_t *self);

// Destruye el arreglo
void arrayDestroy(array_t * self);

#endif //COMMON_ARRAY_H
