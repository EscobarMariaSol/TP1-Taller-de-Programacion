#ifndef COMMON_VIGENERE_ENCODER_H
#define COMMON_VIGENERE_ENCODER_H

#include "common_array.h"

typedef struct {
    char *key;
}vigenere_encoder_t;

// Crea un nuevo encoder
int vigenereEncoderCreate(vigenere_encoder_t *encoder, char *key);

// Codifica el mensaje que se le pasa por parámetro
array_t *vigenereEncoderEncode(vigenere_encoder_t *self, array_t *message);

// Decodifica un mensaje encriptado que se le pasa por parámetro
array_t *vigenereEncoderDecode(vigenere_encoder_t *self, array_t *message);


#endif //COMMON_VIGENERE_ENCODER_H