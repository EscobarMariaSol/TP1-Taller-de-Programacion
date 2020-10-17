#include "common_cesar_encoder.h"

/*********Funciones auxiliares************/

char cesarEncode(uint32_t key, char elem) {
    char aux;
    aux = (char) (((uint32_t) elem) + key);
    return (aux % 256);
}

/*********Primitivas del encoder**********/ 

int cesarEncoderCreate(cesar_encoder_t *encoder, uint32_t key) {
    memset(encoder, 0, sizeof(cesar_encoder_t));
    encoder->key = key;
    return 0;
}

unsigned char cesarEncoderEncode(cesar_encoder_t *self, unsigned char elem) {
    return cesarEncode(self->key, elem);
}

unsigned char cesarEncoderDecode(cesar_encoder_t *self, unsigned char elem) {
    return cesarEncode((-self->key), elem);
}
