#include "common_vigenere_encoder.h"

/************************Funciones auxiliares***********************/

void incrementPos(vigenere_encoder_t *encoder) {
    encoder->key_pos++;
    if (encoder->key_pos == strlen(encoder->key)) encoder->key_pos = 0;
}

/************************Primitivas del encoder***********************/

int vigenereEncoderCreate(vigenere_encoder_t *encoder, char *key) {
    memset(encoder, 0, sizeof(vigenere_encoder_t));
    encoder->key = key;
    encoder->key_pos = 0;
    return 0;
}

unsigned char vigenereEncoderEncode(vigenere_encoder_t *self, 
                                    unsigned char element) {
    unsigned char aux = (element + self->key[self->key_pos]) % 256;
    incrementPos(self);
    return aux;
}


unsigned char vigenereEncoderDecode(vigenere_encoder_t *self, 
                                    unsigned char element) {
    unsigned char aux = (element - self->key[self->key_pos]) % 256;
    incrementPos(self);
    return aux;
}
