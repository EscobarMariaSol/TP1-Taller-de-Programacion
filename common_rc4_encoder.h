#ifndef COMMON_RC4_ENCODER_H
#define COMMON_RC4_ENCODER_H

#include "common_array.h"

typedef struct {
    unsigned char stream[256];
    uint8_t i, j;
}rc4_encoder_t;

// Crea un nuevo encoder
int rc4EncoderCreate(rc4_encoder_t *encoder, unsigned char *key);

// Codifica el mensaje que se le pasa por parámetro
array_t *rc4EncoderEncode(rc4_encoder_t *self, array_t *message);

#endif //COMMON_RC4_ENCODER_H