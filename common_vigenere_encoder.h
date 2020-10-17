#ifndef COMMON_VIGENERE_ENCODER_H
#define COMMON_VIGENERE_ENCODER_H

#include "common_array.h"

typedef struct {
    char *key;
    int key_pos;
}vigenere_encoder_t;

// Crea un nuevo encoder
int vigenereEncoderCreate(vigenere_encoder_t *encoder, char *key);

// Codifica el mensaje que se le pasa por parámetro
unsigned char vigenereEncoderEncode(vigenere_encoder_t *self, 
                                    unsigned char element);

// Decodifica un mensaje encriptado que se le pasa por parámetro
unsigned char vigenereEncoderDecode(vigenere_encoder_t *self, 
                                    unsigned char element);


#endif //COMMON_VIGENERE_ENCODER_H