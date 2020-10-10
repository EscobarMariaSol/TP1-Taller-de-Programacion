#include "common_vigenere_encoder.h"

/************************Funciones auxiliares***********************/

int vigenereEncoder(vigenere_encoder_t *vigenere, array_t *message, array_t *new_message, int code) {
    int i, j = 0;
    for (i = 0; i < arrayGetSize(message); i++) {
        char aux = (arrayGetElement(message, i) + (code * vigenere->key[j])) % 256;
        if (arrayAdd(new_message, &aux, 1) < 0) return -1;
        j++;
        if (j == strlen(vigenere->key)) j = 0; 
    }
    return 0;
}

/************************Primitivas del encoder***********************/

int vigenereEncoderCreate(vigenere_encoder_t *encoder, char *key) {
    memset(encoder, 0, sizeof(vigenere_encoder_t));
    encoder->key = key;
    return 0;
}

array_t *vigenereEncoderEncode(vigenere_encoder_t *self, array_t *message) {
    array_t *new_array = arrayCreate(arrayGetSize(message));
    if (!new_array) return NULL;
    if (vigenereEncoder(self, message, new_array, 1) < 0) {
        arrayDestroy(new_array);
        return NULL;
    }
    return new_array;
}


array_t *vigenereEncoderDecode(vigenere_encoder_t *self, array_t *message) {
    array_t *new_array = arrayCreate(arrayGetSize(message));
    if (!new_array) return NULL;
    if (vigenereEncoder(self, message, new_array, -1) < 0) {
        arrayDestroy(new_array);
        return NULL;
    }
    return new_array;
}
