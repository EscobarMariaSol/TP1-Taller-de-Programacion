#ifndef COMMON_RC4_ENCODER_H
#define COMMON_RC4_ENCODER_H

#include "common_array.h"

typedef struct {
    unsigned char stream[256];
    uint8_t i, j;
}rc4_encoder_t;

// Crea un nuevo encoder que utiliza como método de codificación el
// método rc4
// Pre: recibe un puntero a un rc4_encoder_t creado y una clave numérica
// Pos: el encoder ha sido creado
int rc4EncoderCreate(rc4_encoder_t *encoder, unsigned char *key);

// Codifica el byte que se le pasa por parámetro
// Pre: recibe puntero a un rc4_encoder_t creado y un elemento a codificar
// Pos: devuelve el elemento codificado
unsigned char rc4EncoderEncode(rc4_encoder_t *self, unsigned char element);

#endif //COMMON_RC4_ENCODER_H
