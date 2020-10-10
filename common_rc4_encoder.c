#include "common_rc4_encoder.h"

/************************Funciones auxiliares*************************/

void swap(unsigned char *stream, unsigned int i, unsigned int j) {
    unsigned char aux = stream[i];
    stream[i] = stream[j];
    stream[j] = aux;
}

void rc4Init(rc4_encoder_t *encoder, unsigned char *key) {
    int i, j;
    for (i = 0; i < 256; i++)
        encoder->stream[i] = i;
    for (i = j = 0; i < 256; i++) {
        j = (j + key[i % (strlen((char*)key))] + encoder->stream[i]) & 255;
        swap(encoder->stream, i, j);
    }
}

unsigned char rc4Randomize(rc4_encoder_t *encoder) {
    encoder->i = (encoder->i + 1) & 255;
    encoder->j = (encoder->j + encoder->stream[encoder->i]) & 255;
    swap(encoder->stream, encoder->i, encoder->j);
    return encoder->stream[(encoder->stream[encoder->i] + encoder->stream[encoder->j]) & 255];
}

/************************Primitivas del encoder***********************/

int rc4EncoderCreate(rc4_encoder_t *encoder, unsigned char *key){
    memset(encoder, 0, sizeof(rc4_encoder_t));
    rc4Init(encoder, key);
    encoder->i = 0;
    encoder->j = 0;
    return 0;
}

array_t *rc4EncoderEncode(rc4_encoder_t *self, array_t *message) {
    array_t *new_message = arrayCreate(arrayGetSize(message));
    if (!new_message) return NULL;
    for (int i = 0; i < arrayGetSize(message); i++) {
        char aux = arrayGetElement(message, i) ^ rc4Randomize(self);
        if (arrayAdd(new_message, &aux, 1) < 0) {
            arrayDestroy(new_message);
            return NULL;
        }
    }
    return new_message;
}
