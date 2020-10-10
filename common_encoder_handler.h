#ifndef COMMON_ENCODER_HANDLER_H
#define COMMON_ENCODER_HANDLER_H

#include "common_array.h"
#include "common_cesar_encoder.h"
#include "common_vigenere_encoder.h"
#include "common_rc4_encoder.h"

typedef struct {
    void *encoder;
    char *type;
}encoder_handler_t;


// Crea un manejador según el tipo de método que se quiera utilizar para codificar;
int encoderHandlerCreate(encoder_handler_t *handler, const char *type, void *key);

// Codifica un mensaje de acuerdo al método que se le haya indicado
array_t *encoderHandlerEncode(encoder_handler_t *self, array_t *message);

// Decodifica un mensaje de acuerdo al método que se le haya indicado
array_t *encoderHandlerDecode(encoder_handler_t *self, array_t *message);

#endif //COMMON_ENCODER_HANDLER_H