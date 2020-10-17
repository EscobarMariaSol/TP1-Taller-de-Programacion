#ifndef COMMON_CESAR_ENCODER_H
#define COMMON_CESAR_ENCODER_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
    uint32_t key;
}cesar_encoder_t;

// Crea un nuevo cesar_encoder
int cesarEncoderCreate(cesar_encoder_t *encoder, uint32_t key);

// Codifica el mensaje que se le pasa por parámetro
unsigned char cesarEncoderEncode(cesar_encoder_t *self, unsigned char element);

// Decodifica un mensaje encriptado que se le pasa por parámetro
unsigned char cesarEncoderDecode(cesar_encoder_t *self, unsigned char element);

#endif //COMMON_CESAR_ENCODER_H
