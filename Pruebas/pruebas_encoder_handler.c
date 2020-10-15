#include "common_encoder_handler.h"

int crear_handler(const char *tipo, char *clave) {
    encoder_handler_t handler;
    if (encoderHandlerCreate(&handler, tipo, clave) < 0) 
        return 1;
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, tipo) == 0) ? "OK" : "FALLÓ");
    return 0;
}

int cifrar_mensaje_cesar(void) {
    char *message = "Pan";
    char *key = "5";
    uint32_t codigo_esperado[] = {0x55, 0x66, 0x73};
    encoder_handler_t handler;
    if (encoderHandlerCreate(&handler, "Cesar", key) < 0) 
        return 1;
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, "Cesar") == 0) ? "OK" : "FALLÓ");
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, (unsigned char*) message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *cifrado = encoderHandlerEncode(&handler, arreglo);
    if (!cifrado) return 1;
    
    bool esta_ok = true;
    for (int i = 0; i < 3; i++) {
        if (arrayGetElement(cifrado, i) != ((char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    arrayDestroy(arreglo);
    arrayDestroy(cifrado);
    return !esta_ok;
}

int cifrar_mensaje_vigenere(void) {
    char *clave = "SecureKey";
    char *message = "Secret Message";
    uint32_t codigo_esperado[] = {
        ('S' + 'S'), ('e' + 'e'), ('c' + 'c'), ('u' + 'r'), ('r' + 'e'),
        ('e' + 't'), ('K' + ' '), ('e' + 'M'), ('y' + 'e'), ('S' + 's'), 
        ('e' + 's'), ('c' + 'a'), ('u' + 'g'), ('r' + 'e')};
    encoder_handler_t handler;

    if (encoderHandlerCreate(&handler, "vigenerE", clave) < 0) return 1;
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, "vigenerE") == 0) ? "OK" : "FALLÓ");
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, (unsigned char*) message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *codificado = encoderHandlerEncode(&handler, arreglo);
    printf("EL MENSAJE SE CODIFICÓ: %s\n", (codificado != NULL) ? "OK" : "FALLÓ"); 
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1;
    }
    bool esta_ok = true;
    for (int i = 0; i < 14; i++) {
        if (arrayGetElement(codificado, i) != ((unsigned char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE CODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    arrayDestroy(codificado);
    arrayDestroy(arreglo);
    return !esta_ok;
}

int cifrar_mensaje_rc4() {
    char *clave = "Key";
    char *message = "Plaintext";
    uint32_t codigo_esperado[] = {0xBB, 0xF3, 0x16, 0xE8, 0xD9, 0x40, 0xAF, 0x0A, 0xD3};
    encoder_handler_t handler;

    if (encoderHandlerCreate(&handler, "RC4", clave) < 0) return 1;
   
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, "RC4") == 0) ? "OK" : "FALLÓ");
   
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, (unsigned char*) message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *codificado = encoderHandlerEncode(&handler, arreglo);
    printf("EL MENSAJE SE CODIFICÓ: %s\n", (codificado != NULL) ? "OK" : "FALLÓ"); 
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1;
    }
    
    bool esta_ok = true;
    for (int i = 0; i < 9; i++) {
        if (arrayGetElement(codificado, i) != ((unsigned char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE CODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    arrayDestroy(codificado);
    arrayDestroy(arreglo);
    return !esta_ok;
}

int cifrar_y_descifrar_mensaje_cesar(void) {
    char *message = "Mensaje secreto";
    char *key = "3";
    uint32_t codigo_esperado[] = {0x50, 0x68, 0x71, 0x76, 0x64, 0x6d,
            0x68, 0x23, 0x76, 0x68, 0x66, 0x75, 0x68, 0x77, 0x72};
    encoder_handler_t handler;
    if (encoderHandlerCreate(&handler, "Cesar", key) < 0) 
        return 1;
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, "Cesar") == 0) ? "OK" : "FALLÓ");
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, (unsigned char*) message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *cifrado = encoderHandlerEncode(&handler, arreglo);
    if (!cifrado) {
        arrayDestroy(arreglo);
        return 1;
    }
    
    bool esta_ok = true;
    for (int i = 0; i < strlen(message); i++) {
        if (arrayGetElement(cifrado, i) != ((char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    encoder_handler_t handler2;
    if (encoderHandlerCreate(&handler2, "Cesar", key) < 0) {
        arrayDestroy(arreglo);
        arrayDestroy(cifrado);
        return 1;
    }
    array_t *descifrado = encoderHandlerDecode(&handler2, cifrado);
    if (!descifrado) {
        arrayDestroy(arreglo);
        arrayDestroy(cifrado);
        return 1;
    }

    for (int i = 0; i < strlen(message); i++) {
        if (arrayGetElement(descifrado, i) != ((char) message[i])) {
            esta_ok = false;
            break;
        } 
    }
    arrayDestroy(arreglo);
    arrayDestroy(cifrado);
    arrayDestroy(descifrado);
    return !esta_ok;
}

int cifrar_y_descifrar_mensaje_vigenere(void) {
    char *clave = "Secreta";
    char *message = "Mensaje Privado";
    uint32_t codigo_esperado[] = {
        ('S' + 'M'), ('e' + 'e'), ('c' + 'n'), ('r' + 's'), ('e' + 'a'),
        ('t' + 'j'), ('a' + 'e'), ('S' + ' '), ('e' + 'P'), ('c' + 'r'), 
        ('r' + 'i'), ('e' + 'v'), ('t' + 'a'), ('a' + 'd'), ('S' + 'o')};
    encoder_handler_t handler;

    if (encoderHandlerCreate(&handler, "vigenerE", clave) < 0) return 1;
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, "vigenerE") == 0) ? "OK" : "FALLÓ");
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, (unsigned char*) message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *codificado = encoderHandlerEncode(&handler, arreglo);
    printf("EL MENSAJE SE CODIFICÓ: %s\n", (codificado != NULL) ? "OK" : "FALLÓ"); 
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1;
    }
    bool esta_ok = true;
    for (int i = 0; i < 14; i++) {
        if (arrayGetElement(codificado, i) != ((unsigned char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE CODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    
    encoder_handler_t handler2;
    if (encoderHandlerCreate(&handler2, "VigenErE", clave) < 0) {
        arrayDestroy(arreglo);
        arrayDestroy(codificado);
        return 1;
    }
    array_t *descifrado = encoderHandlerDecode(&handler2, codificado);
    if (!descifrado) {
        arrayDestroy(arreglo);
        arrayDestroy(codificado);
        return 1;
    }

    for (int i = 0; i < strlen(message); i++) {
        if (arrayGetElement(descifrado, i) != ((unsigned char) message[i])) {
            esta_ok = false;
            break;
        } 
    }
    arrayDestroy(arreglo);
    arrayDestroy(codificado);
    arrayDestroy(descifrado);
    return !esta_ok;
}

int cifrar_y_descifrar_mensaje_rc4() {
    char *clave = "Cervantes";
    char *message = "En un lugar de la mancha";
    uint32_t codigo_esperado[] = {0x6D, 0x11, 0xFB, 0x9B, 0x96, 0x4C, 0xA1,
            0xFC, 0xD6, 0x80, 0xA5, 0x8C, 0xB5, 0x7D, 0xC2, 0x0A, 0x28, 0x07, 0x94,
            0x1C, 0x01, 0xF9, 0xC7, 0xA3};
    encoder_handler_t handler;

    if (encoderHandlerCreate(&handler, "RC4", clave) < 0) return 1;
   
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, "RC4") == 0) ? "OK" : "FALLÓ");
   
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, (unsigned char*) message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *codificado = encoderHandlerEncode(&handler, arreglo);
    printf("EL MENSAJE SE CODIFICÓ: %s\n", (codificado != NULL) ? "OK" : "FALLÓ"); 
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1;
    }
    
    bool esta_ok = true;
    for (int i = 0; i < 9; i++) {
        if (arrayGetElement(codificado, i) != ((unsigned char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE CODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    encoder_handler_t handler2;
    if (encoderHandlerCreate(&handler2, "Rc4", clave) < 0) {
        arrayDestroy(arreglo);
        arrayDestroy(codificado);
        return 1;
    }
    array_t *descifrado = encoderHandlerDecode(&handler2, codificado);
    if (!descifrado) {
        arrayDestroy(arreglo);
        arrayDestroy(codificado);
        return 1;
    }

    for (int i = 0; i < strlen(message); i++) {
        if (arrayGetElement(descifrado, i) != ((unsigned char) message[i])) {
            esta_ok = false;
            break;
        } 
    }
    arrayDestroy(arreglo);
    arrayDestroy(codificado);
    arrayDestroy(descifrado);
    return !esta_ok;
}

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("**********************PRUEBAS HANDLER ENCODER************************\n");

    printf("*****************CREAR UN HANDLER CON CESAR ENCODER***********\n");
    resp = crear_handler("CESAR", "10");
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("*****************CREAR UN HANDLER CON VIGENERE ENCODER**************\n");
    resp = crear_handler("VIGENEre", "Key");
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CREAR UN HANDLER CON RC4 ENCODER***********************\n");
    resp = crear_handler("rc4", "key");
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CREAR UN HANDLER CON ENCODER ERRONEO***********************\n");
    resp = crear_handler("Casa", "key");
    printf("EL ENCODER NO SE CREO: %s\n", (resp) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR UN MENSAJE CESAR********************************\n");
    resp = cifrar_mensaje_cesar();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR UN MENSAJE VIGENERE*****************************\n");
    resp = cifrar_mensaje_vigenere();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR UN MENSAJE RC4*****************************\n");
    resp = cifrar_mensaje_rc4();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR Y DESCIFRAR UN MENSAJE CESAR***********************\n");
    resp = cifrar_y_descifrar_mensaje_cesar();
    printf("EL ENCODER CIFRÓ Y DESCIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR Y DESCIFRAR UN MENSAJE VIGENERE***********************\n");
    resp = cifrar_y_descifrar_mensaje_vigenere();
    printf("EL ENCODER CIFRÓ Y DESCIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR Y DESCIFRAR UN MENSAJE RC4***********************\n");
    resp = cifrar_y_descifrar_mensaje_rc4();
    printf("EL ENCODER CIFRÓ Y DESCIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    return 0;
}