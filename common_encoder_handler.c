#include "common_encoder_handler.h"

/************************Funciones Auxiliares*********************************/

bool isCesar(const char *type) {
    char *cesar = "CESAR";
    for (int i = 0; i < strlen(cesar); i++)
        if (toupper(type[i]) != cesar[i]) return false;
    return true; 
}

bool isValidKey(const char *key) {
    for (int i = 0; i < strlen(key); i++)
        if (!isdigit(key[i])) return false;
    return true;
}

bool isVigenere(const char *type) {
    char *vigenere = "VIGENERE";
    for (int i = 0; i < strlen(vigenere); i++)
        if (toupper(type[i]) != vigenere[i]) return false;
    return true; 
}

bool isRc4(const char *type) {
    char *rc4 = "RC4";
    for (int i = 0; i < strlen(rc4); i++)
        if (toupper(type[i]) != rc4[i]) return false;
    return true; 
}


int setEncoder(encoder_handler_t *handler, const char *type, const char *key) {
    if (isCesar(type) && isValidKey(key)) {
        uint32_t new_key = atoi(key);
        return cesarEncoderCreate(&handler->cesar_encoder, new_key);
    } else if (isVigenere(type)) {
        return vigenereEncoderCreate(&handler->vigenere_encoder, (char*)key);
    } else if (isRc4(type)) {
        return rc4EncoderCreate(&handler->rc4_encoder, (unsigned char*)key);
    }
    return -1;
}

unsigned char encoderEncode(encoder_handler_t *handler, unsigned char element) {
    if (isCesar(handler->type)) {
        return cesarEncoderEncode(&handler->cesar_encoder, element);
    } else if (isVigenere(handler->type)) {
        return vigenereEncoderEncode(&handler->vigenere_encoder, element);
    } else if (isRc4(handler->type)) {
        return rc4EncoderEncode(&handler->rc4_encoder, element);
    } 
    return -1;
}

unsigned char encoderDecode(encoder_handler_t *handler, unsigned char element) {
    if (isCesar(handler->type)) {
        return cesarEncoderDecode(&handler->cesar_encoder, element);
    } else if (isVigenere(handler->type)) {
        return vigenereEncoderDecode(&handler->vigenere_encoder, element);
    } else if (isRc4(handler->type)) {
        return rc4EncoderEncode(&handler->rc4_encoder, element);
    } 
    return -1;
}

array_t *codingHandler(encoder_handler_t *handler, array_t *message, 
    unsigned char (*encodeDecode)(encoder_handler_t *handler, unsigned char element)) {
    array_t *new_message = arrayCreate(arrayGetSize(message));
    if (!new_message) return NULL;
    for (int i = 0; i < arrayGetSize(message); i++) {
        unsigned char aux = encodeDecode(handler, arrayGetElement(message, i));
        if (arrayAdd(new_message, &aux, 1) < 0) {
            arrayDestroy(new_message);
            return NULL;
        }
    }
    return new_message;
}

/************************Primitivas del encoder handler***********************/

int encoderHandlerCreate(encoder_handler_t *handler, const char *type, const char *key) {
    memset(handler, 0, sizeof(encoder_handler_t));
    if (setEncoder(handler, type, key) < 0) return -1;
    handler->type = type;
    return 0;
}

array_t *encoderHandlerEncode(encoder_handler_t *self, array_t *message) {
    return codingHandler(self, message, encoderEncode);
}

array_t *encoderHandlerDecode(encoder_handler_t *self, array_t *message) {
    return codingHandler(self, message, encoderDecode);
}

void encoderHandlerDestroy(encoder_handler_t *self) {
    
}
