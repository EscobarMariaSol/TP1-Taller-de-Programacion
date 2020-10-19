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

// Estructura del codificador Cesar
// Cuenta con un único atributo que corresponde a la clave que se 
// utiliza a la hora de codificar un byte.
typedef struct {
    uint32_t key;
}cesar_encoder_t;

// Crea un nuevo cesar_encoder
// Pre: recibe un puntero a un cesar_encoder_t y una clave numérica
// Post: se ha creado un nuevo cesar_encoder_t
int cesarEncoderCreate(cesar_encoder_t *encoder, uint32_t key);

// Codifica el byte que se le pasa por parámetro
// Pre: el encoder ha sido creado
// Post: el byte ha sido codificado
unsigned char cesarEncoderEncode(cesar_encoder_t *self, unsigned char element);

// Decodifica un byte encriptado que se le pasa por parámetro
// Pre: el encoder ha sido creado
// Post: el byte ha sido decodificado
unsigned char cesarEncoderDecode(cesar_encoder_t *self, unsigned char element);

#endif //COMMON_CESAR_ENCODER_H
