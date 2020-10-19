#ifndef COMMON_INPUT_OUTPUT_HANDLER_H
#define COMMON_INPUT_OUTPUT_HANDLER_H

#include "common_array.h"

// Estructura del manejador de Entrada y Salida
// Cuenta con un único atributo correspondiente al file en el cual
// deberá escribir o leer.
typedef struct {
    FILE *file;
}io_handler_t;

// Crea un nuevo manejador de entrada y salida 
// Pre: recibe un puntero a un io_handler_t creado y el
// path de un archivo, si no recibe el path se asignará la
// entrada estándar
// Pos: devuelve 0 si el handler se creo correctamente o -1 en caso contrario
int ioHandlerCreate(io_handler_t *handler, const char *path);

// Devuleve el contenido desde el archivo especificado al momento
// de la creación del manejador
// Pre: recibe un puntero a un io_handler_t creado
// Pos: lee y devuelve el contenido del file o stdin, en un array_t,
// en caso de error devuelve un puntero a NULL
array_t *ioHandlerGetMessage(io_handler_t * self);

// Copia el contenido del mensaje especificado en el archivo indicado
// o lo muestra a través de la salida estándar
// Pre: recibe un puntero a un handler creado y un mensaje en un array_t
// Pos: devuelve 0 si el mensaje se ha copiado correctamente, -1 en 
// caso contrario
int ioHandlerSetMessage(io_handler_t * self, array_t *message);

// Destruye el manejador de archivo que se le pasa por parámetro
// Pre: el puntero conrresponde a un io_handler_t creado
// Pos: el handler ha sido destruido correctamente
void ioHandlerDestroy(io_handler_t * self);

#endif //COMMON_INPUT_OUTPUT_HANDLER_H
