#ifndef COMMON_ENCODER_HANDLER_H
#define COMMON_ENCODER_HANDLER_H

#include <ctype.h>
#include "common_array.h"
#include "common_cesar_encoder.h"
#include "common_vigenere_encoder.h"
#include "common_rc4_encoder.h"

typedef struct {
    cesar_encoder_t cesar_encoder;
    vigenere_encoder_t vigenere_encoder;
    rc4_encoder_t rc4_encoder;
    const char *type;
}encoder_handler_t;


// Crea un manejador que se encarga de aplicar los tipos de 
// codificadores que correspondan
// Pre: Recibe un puntero a un encoder_handler_t creado, un tipo de
// codificador válido, y la clave a aplicar en el mismo
// Pos: devulve 0 si el manejador se creó, -1 en caso contrario.
int encoderHandlerCreate(encoder_handler_t *handler, 
                        const char *type, const char *key);

// Codifica un mensaje de acuerdo al método que se le haya indicado
// Pre: recibe un puntero a un encoder_handler_t creado y un puntero array_t
// que contiene el mensaje a codificar
// Pos: devuelve un puntero al mensaje codificado en caso de exito, 
// sino devuelve un puntero a NULL
array_t *encoderHandlerEncode(encoder_handler_t *self, array_t *message);

// Decodifica un mensaje de acuerdo al método que se le haya indicado
// Pre: recibe un puntero a un encoder_handler_t creado y un puntero array_t
// que contiene el mensaje a decodificar
// Pos: devuelve un puntero al mensaje decodificado en caso de exito, 
// sino devuelve un puntero a NULL
array_t *encoderHandlerDecode(encoder_handler_t *self, array_t *message);

// Destruye el manejador que se le pasa por parámetro
// Pre: recibe un puntero a un encoder_handler_t creado
// pos: el handler ha sido destruido
void encoderHandlerDestroy(encoder_handler_t *self);

#endif //COMMON_ENCODER_HANDLER_H
