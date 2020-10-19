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

// Estructura del array
// Cuenta con atributos como un buffer que será en el cual se almacenará la 
// información, el tamaño del buffer y la posición del buffer en la que se 
// encuentra posicionado.
typedef struct {
    unsigned char *buffer;
    size_t size;
    uint32_t pos;
}array_t;

// Crea un arreglo del tipo array_t con el tamaño indicado por parámetro
// Pre: recibe un tamaño mayor o igual a cero
// Post: devuelve un array de tamaño size
array_t* arrayCreate(size_t size);

// Copia un mensaje al final del arreglo que se le pasa por parámetro
// Pre: recibe un puntero a un array válido, un mensaje y su longitud
// Post: el mensaje ha sido copiado al final del array
int arrayAdd(array_t *self, const unsigned char *msg, size_t len);

// Devuelve el contenido dentro del arreglo que se le pasa por parámetro
// Pre: recibe un array válido
// Post: devuelve el contenido alamacenado dentro del array
unsigned char *arrayGetContent(array_t *self);

// Devuelve el caracter que se encuentra en la posición pos
// Pre: recibe un array válido y una posición válida del array
// Post: devuelve el caracter que se encuentra en la posición pos
unsigned char arrayGetElement(array_t *self, size_t pos);

// Devuelve el largo del arreglo que se le pasa por parámetro
// Pre: recibe un array válido
// Post: devuelve la longitud del arreglo
size_t arrayGetSize(array_t *self);

// Destruye el arreglo que se le pasa por parámetro
// Pre: el array ha sido creado
// Post: el array fue destruido 
void arrayDestroy(array_t * self);

#endif //COMMON_ARRAY_H
