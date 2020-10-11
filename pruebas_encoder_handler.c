#include "common_encoder_handler.h"

int crear_handler(const char *tipo, void *clave) {
    encoder_handler_t handler;
    if (encoderHandlerCreate(&handler, tipo, clave) < 0) 
        return 1;
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, tipo) == 0) ? "OK" : "FALLÓ");
    return 0;
}

int cifrar_mensaje_cesar(void) {
    char *message = "Pan";
    int key = 5;
    uint32_t codigo_esperado[] = {0x55, 0x66, 0x73};
    encoder_handler_t handler;
    if (encoderHandlerCreate(&handler, "Cesar", &key) < 0) 
        return 1;
    printf("TIPO COINCIDE: %s\n", (strcmp(handler.type, "Cesar") == 0) ? "OK" : "FALLÓ");
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, message, strlen(message)) < 0) {
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
    if (arrayAdd(arreglo, message, strlen(message)) < 0) {
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
        if (arrayGetElement(codificado, i) != ((char) codigo_esperado[i])) {
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
    if (arrayAdd(arreglo, message, strlen(message)) < 0) {
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
        if (arrayGetElement(codificado, i) != ((char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE CODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    arrayDestroy(codificado);
    arrayDestroy(arreglo);
    return !esta_ok;
}

/*int cifrar_y_descifrar_mensaje(void) {
    char *clave = "SecureKey";
    char *message = "Secret Message";
    vigenere_encoder_t encoder;
    if (vigenereEncoderCreate(&encoder, clave) < 0) 
        return 1;
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) 
        return 1;
    if (arrayAdd(arreglo, message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    printf("CLAVE COINCIDE: %s\n", (encoder.key == clave) ? "OK" : "FALLÓ");
    array_t *codificado = vigenereEncoderEncode(&encoder, arreglo);
    printf("EL MENSAJE SE CODIFICÓ: %s\n", (codificado != NULL) ? "OK" : "FALLÓ"); 
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *decodificado = vigenereEncoderDecode(&encoder, codificado);
    if (!decodificado) {
        arrayDestroy(arreglo);
        arrayDestroy(codificado);
        return 1;
    }
    bool esta_ok = true;
    for (int i = 0; i < 14; i++) {
        if (arrayGetElement(decodificado, i) != message[i]) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE DECODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    arrayDestroy(decodificado);
    arrayDestroy(codificado);
    arrayDestroy(arreglo);
    return !esta_ok;
}*/

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("**********************PRUEBAS HANDLER ENCODER************************\n");

    printf("*****************CREAR UN HANDLER CON CESAR ENCODER***********\n");
    int clave = 5;
    resp = crear_handler("CESAR", &clave);
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("*****************CREAR UN HANDLER CON VIGENERE ENCODER**************\n");
    resp = crear_handler("VIGENEre", "Key");
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CREAR UN HANDLER CON RC4 ENCODER***********************\n");
    resp = crear_handler("rc4", "key");
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR UN MENSAJE CESAR********************************\n");
    resp = cifrar_mensaje_cesar();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR UN MENSAJE VIGENERE*****************************\n");
    resp = cifrar_mensaje_vigenere();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR UN MENSAJE RC4*****************************\n");
    resp = cifrar_mensaje_rc4();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    /*printf("**********************CIFRAR Y DESCIFRAR UN MENSAJE***********************\n");
    resp = cifrar_y_descifrar_mensaje();
    printf("EL ENCODER CIFRÓ Y DESCIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");*/
    
    return 0;
}