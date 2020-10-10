#include "common_encoder_handler.h"

/************************Funciones Auxiliares*********************************/

char *to_upper_case(char *text) {
    for (int i = 0; i < strlen(text); i++) {
        text[i] = toupper(text[i]);
    }
    return text;
}

int selectEncoder(void *encoder, const char type, void *key) {
    if (to_upper_case(type) == "CESAR") {
        uint32_t *new_key = (uint32_t*) key;
        return cesarEncoderCreate((cesar_encoder_t*)encoder, *new_key);
    } else if (to_upper_case(type) == "VIGENERE") {
        return vigenereEncoderCreate((vigenere_encoder_t*)encoder, (char*)key);
    } else if (to_upper_case(type) == "RC4") {
        return rc4EncoderCreate((rc4_encoder_t*)encoder, (unsigned char*)key);
    } 
    return -1; 
}

char encoderEncode(encoder_handler_t *handler, char element) {
    if (handler->type == "CESAR") {
        return cesarEncoderEncode((cesar_encoder_t*)handler->encoder, element);
    } else if (handler->type == "VIGENERE") {
        return vigenereEncoderEncode((vigenere_encoder_t*)handler->encoder, element);
    } else if (handler->type == "RC4") {
        return rc4EncoderEncode((rc4_encoder_t*)handler->encoder, element);
    } 
    return -1;
}

/************************Primitivas del encoder handler***********************/

int encoderHandlerCreate(encoder_handler_t *handler, const char *type, void *key) {
    memset(handler, 0, sizeof(encoder_handler_t));
    void *new_encoder;
    if (selectEncoder(new_encoder, type, key) < 0) return -1;
    handler->encoder = new_encoder;
    handler->type = to_upper_case(type);
    return 0;
}

array_t *encoderHandlerEncode(encoder_handler_t *self, array_t *message) {
    array_t *new_message = arrayCreate(arrayGetSize(message));
    if (!new_message) return NULL;
    for (int i = 0; i < arrayGetSize(message); i++) {
        char aux = encoderEncode(self, arrayGetElement(message, i));
        if (arrayAdd(new_message, &aux, 1) < 0) {
            arrayDestroy(new_message);
            return NULL;
        }
    }
    return new_message;
}


array_t *encoderHandlerDecode(encoder_handler_t *handler, array_t *message);
