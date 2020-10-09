#include "common_vigenere_encoder.h"

/************************Primitivas del encoder***********************/

int vigenereEncoderCreate(vigenere_encoder_t *encoder, char *key) {
    memset(encoder, 0, sizeof(vigenere_encoder_t));
    encoder->key = key;
    return 0;
}

array_t *vigenereEncoderEncode(vigenere_encoder_t *self, array_t *message) {
    array_t *new_array = arrayCreate(arrayGetSize(message));
    if (!new_array) return NULL;
    int i, j = 0;
    for (i = 0; i < arrayGetSize(message); i++) {
        char aux = (arrayGetElement(message, i) + self->key[j]);
        if (arrayAdd(new_array, &aux, 1) < 0) {
            arrayDestroy(new_array);
            return NULL;
        }
        j++;
        if (j == strlen(self->key)) j = 0; 
    }
    return new_array;
}


array_t *vigenereEncoderDecode(vigenere_encoder_t *self, array_t *message) {
    array_t *new_array = arrayCreate(arrayGetSize(message));
    if (!new_array) return NULL;
    int i, j = 0;
    for (i = 0; i < arrayGetSize(message); i++) {
        char aux = (arrayGetElement(message, i) - self->key[j]);
        if (arrayAdd(new_array, &aux, 1) < 0) {
            arrayDestroy(new_array);
            return NULL;
        }
        j++;
        if (j == strlen(self->key)) j = 0; 
    }
    return new_array;
}
