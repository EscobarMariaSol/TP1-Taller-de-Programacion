#ifndef COMMON_VIGENERE_ENCODER_H
#define COMMON_VIGENERE_ENCODER_H

#include "common_array.h"

// Estructura del codificador Vigenere
// Cuenta con atributos como la clave (key) y la 
// posición actual de la clave en la que se encuentra (key_pos)
// de esta manera se puede codificar o decodificar un mensaje completo, 
// llamando al método del encoder las veces que sean necesarias.
typedef struct {
    char *key;
    int key_pos;
}vigenere_encoder_t;

// Crea un nuevo vigenere encoder
// Pre: recibe un puntero a un vigenere_encoder_t y una clave
// Pos: devuelve 0 si el encoder se ha creado correctamente
// o -1 en caso de error
int vigenereEncoderCreate(vigenere_encoder_t *encoder, char *key);

// Codifica el elemento que se le pasa por parámetro
// Pre: recibe un puntero a un vigenere_encoder_t creado y un elemento
// a codificar
// Pos: devuelve el elemento que ha sido codificado
unsigned char vigenereEncoderEncode(vigenere_encoder_t *self, 
                                    unsigned char element);

// Decodifica un elemento encriptado que se le pasa por parámetro
// Pre: recibe un puntero a un vigenere_encoder_t creado y un elemento
// a decodificar
// Pos: devuelve el elemento decodificado
unsigned char vigenereEncoderDecode(vigenere_encoder_t *self, 
                                    unsigned char element);

#endif //COMMON_VIGENERE_ENCODER_H
