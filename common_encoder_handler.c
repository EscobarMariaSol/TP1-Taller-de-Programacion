#include "common_encoder_handler.h"

/************************Funciones Auxiliares*********************************/

// Indica verdader o falso según si el nombre enviado es Cesar o no
// Pre: recibe una cadena de caracteres
// Pos: Devuelve true si la cadena es "cesar" o false en caso contrario
bool isCesar(const char *type) {
    char *cesar = "CESAR";
    for (int i = 0; i < strlen(cesar); i++)
        if (toupper(type[i]) != cesar[i]) return false;
    return true; 
}

// Indica si una clave es válida
// Pre: recibe una cadena de caracteres
// Pos: devuelve tru si la cadena corresponde a un número
// o false en caso contrario
bool isValidKey(const char *key) {
    for (int i = 0; i < strlen(key); i++)
        if (!isdigit(key[i])) return false;
    return true;
}

// Indica verdader o falso según si el nombre enviado es Vigenere o no
// Pre: recibe una cadena de caracteres
// Pos: Devuelve true si la cadena es "vigenere" o false en caso contrario
bool isVigenere(const char *type) {
    char *vigenere = "VIGENERE";
    for (int i = 0; i < strlen(vigenere); i++)
        if (toupper(type[i]) != vigenere[i]) return false;
    return true; 
}

// Indica verdader o falso según si el nombre enviado es RC4 o no
// Pre: recibe una cadena de caracteres
// Pos: Devuelve true si la cadena es igual a "RC4" o false en caso contrario
bool isRc4(const char *type) {
    char *rc4 = "RC4";
    for (int i = 0; i < strlen(rc4); i++)
        if (toupper(type[i]) != rc4[i]) return false;
    return true; 
}

// Asigna el tipo de encoder que se utilizará para codificar
// Pre: recibe un puntero a encoder_handler_t, un tipo de encoder y la clave
// Pos: el encoder correcto ha sido asignado
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

// Codifica un byte aplicando el tipo de encoder que corresponde
// pre: recibe un puntero a encoder_handler_t creado y un byte
// Pos: el byte se ha codificado correctamente
unsigned char encoderEncode(encoder_handler_t *handler, unsigned char elem) {
    if (isCesar(handler->type)) {
        return cesarEncoderEncode(&handler->cesar_encoder, elem);
    } else if (isVigenere(handler->type)) {
        return vigenereEncoderEncode(&handler->vigenere_encoder, elem);
    } else if (isRc4(handler->type)) {
        return rc4EncoderEncode(&handler->rc4_encoder, elem);
    }  
    return -1;
}

// Decodifica un byte aplicando el tipo de encoder que corresponde
// pre: recibe un puntero a encoder_handler_t creado y un byte
// Pos: el byte se ha decodificado correctamente
unsigned char encoderDecode(encoder_handler_t *handler, unsigned char elem) {
    if (isCesar(handler->type)) {
        return cesarEncoderDecode(&handler->cesar_encoder, elem);
    } else if (isVigenere(handler->type)) {
        return vigenereEncoderDecode(&handler->vigenere_encoder, elem);
    } else if (isRc4(handler->type)) {
        return rc4EncoderEncode(&handler->rc4_encoder, elem);
    } 
    return -1;
}

// Codifica o decodifica un mensaje de acuerdo al tipo de funció que se le pase
// Pre: recibe un puntero encoder_handler_t creado, un puntero a la función para
// codificar o decodificar y el mensaje a ser codificado
// Pos: devuelve el mensaje codificado o NULL en caso de error
array_t *codingHandler(encoder_handler_t *handler, array_t *msg, unsigned char 
        (*encodeDecode)(encoder_handler_t *handler, unsigned char elem)) {
    array_t *new_message = arrayCreate(arrayGetSize(msg));
    if (!new_message) return NULL;
    for (int i = 0; i < arrayGetSize(msg); i++) {
        unsigned char aux = encodeDecode(handler, arrayGetElement(msg, i));
        if (arrayAdd(new_message, &aux, 1) < 0) {
            arrayDestroy(new_message);
            return NULL;
        }
    }
    return new_message;
}

/************************Primitivas del encoder handler***********************/

int encoderHandlerCreate(encoder_handler_t *handler, 
        const char *type, const char *key) {
    memset(handler, 0, sizeof(encoder_handler_t));
    if (setEncoder(handler, type, key) < 0) return -1;
    handler->type = type;
    return 0;
}

array_t *encoderHandlerEncode(encoder_handler_t *self, array_t *msg) {
    return codingHandler(self, msg, encoderEncode);
}

array_t *encoderHandlerDecode(encoder_handler_t *self, array_t *msg) {
    return codingHandler(self, msg, encoderDecode);
}

void encoderHandlerDestroy(encoder_handler_t *self) { 
}
