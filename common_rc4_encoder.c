#include "common_rc4_encoder.h"

/************************Funciones auxiliares*************************/

// Intercambia 2 valores que se encuentran dentro de un stream de datos
// Pre: recibe un puntero a un stream de datos y dos posiciones válidas
// Pos: los valores de las posiciones indicadas han sido intercambiados
void swap(unsigned char *stream, unsigned int i, unsigned int j) {
    unsigned char aux = stream[i];
    stream[i] = stream[j];
    stream[j] = aux;
}

// Inicializa el encoder que utiliza como método de codificación el 
// método RC4, utilizando la clave que se le pasa por parametro
// Pre: recibe un puntero a un rc4_encoder_t y una clave numérica
// Pos: el encoder ha sido inicializado adecuadamente
void rc4Init(rc4_encoder_t *rc4, unsigned char *key) {
    int i, j;
    for (i = 0; i < 256; i++)
        rc4->stream[i] = i;
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % (strlen((char*)key))] + rc4->stream[i]) & 255;
        swap(rc4->stream, i, j);
    }
}

// Genera un valor random utilizando la información del encoder 
// que se le ha pasado por parámetro
// Pre: recibe un puntero a un rc4_encoder_t creado
// Pos: devuelve un valor aleatorio
unsigned char rc4Randomize(rc4_encoder_t *rc4) {
    rc4->i = (rc4->i + 1) & 255;
    rc4->j = (rc4->j + rc4->stream[rc4->i]) & 255;
    swap(rc4->stream, rc4->i, rc4->j);
    return rc4->stream[(rc4->stream[rc4->i] + rc4->stream[rc4->j]) & 255];
}

/************************Primitivas del rc4***********************/

int rc4EncoderCreate(rc4_encoder_t *rc4, unsigned char *key){
    memset(rc4, 0, sizeof(rc4_encoder_t));
    rc4Init(rc4, key);
    rc4->i = 0;
    rc4->j = 0;
    return 0;
}

unsigned char rc4EncoderEncode(rc4_encoder_t *self, unsigned char element) {
    return (element ^ rc4Randomize(self));
}
