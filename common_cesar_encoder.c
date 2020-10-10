#include "common_cesar_encoder.h"

/*********Funciones auxiliares************/

char cesarEncode(uint32_t key, char element) {
    char aux;
    aux = (char) (((uint32_t) element) + key);
    return (aux % 256);
}

/*********Primitivas del encoder**********/ 

int cesarEncoderCreate(cesar_encoder_t *encoder, uint32_t key) {
    memset(encoder, 0, sizeof(cesar_encoder_t));
    encoder->key = key;
    return 0;
}

// Codifica el mensaje que se le pasa por parámetro
unsigned char cesarEncoderEncode(cesar_encoder_t *self, unsigned char element) {
    return cesarEncode(self->key, element);
}

// Decodifica un mensaje encriptado que se le pasa por parámetro
unsigned char cesarEncoderDecode(cesar_encoder_t *self, unsigned char element) {
    return cesarEncode((-self->key), element);
}
