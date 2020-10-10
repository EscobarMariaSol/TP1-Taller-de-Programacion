#include "common_vigenere_encoder.h"

int crear_vigenere_encoder(char *clave) {
    vigenere_encoder_t encoder;
    if (vigenereEncoderCreate(&encoder, clave) < 0) 
        return 1;
    printf("CLAVE COINCIDE: %s\n", (encoder.key == clave) ? "OK" : "FALLÓ");
    printf("POS INICIAL ES CERO: %s\n", (encoder.key_pos == 0) ? "OK" : "FALLÓ");
    return 0;
}

int cifrar_mensaje(void) {
    char *clave = "SecureKey";
    char *message = "Secret Message";
    uint32_t codigo_esperado[] = {
        ('S' + 'S'), ('e' + 'e'), ('c' + 'c'), ('u' + 'r'), ('r' + 'e'),
        ('e' + 't'), ('K' + ' '), ('e' + 'M'), ('y' + 'e'), ('S' + 's'), 
        ('e' + 's'), ('c' + 'a'), ('u' + 'g'), ('r' + 'e')};
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
    
    array_t *codificado = arrayCreate(arrayGetSize(arreglo));
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1; 
    }
    
    for (int i = 0; i < arrayGetSize(arreglo); i++) {
        char aux = vigenereEncoderEncode(&encoder, (unsigned char) arrayGetElement(arreglo, i));
        if (arrayAdd(codificado, &aux, 1) < 0) {
            arrayDestroy(arreglo);
            arrayDestroy(codificado);
            return 1;
        }
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

int cifrar_y_descifrar_mensaje(void) {
    char *clave = "SecureKey";
    char *message = "Secret Message";
    uint32_t codigo_esperado[] = {
        ('S' + 'S'), ('e' + 'e'), ('c' + 'c'), ('u' + 'r'), ('r' + 'e'),
        ('e' + 't'), ('K' + ' '), ('e' + 'M'), ('y' + 'e'), ('S' + 's'), 
        ('e' + 's'), ('c' + 'a'), ('u' + 'g'), ('r' + 'e')};
    
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
    
    array_t *codificado = arrayCreate(arrayGetSize(arreglo));
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1; 
    }
    
    for (int i = 0; i < arrayGetSize(arreglo); i++) {
        char aux = vigenereEncoderEncode(&encoder, (unsigned char) arrayGetElement(arreglo, i));
        if (arrayAdd(codificado, &aux, 1) < 0) {
            arrayDestroy(arreglo);
            arrayDestroy(codificado);
            return 1;
        }
    }

    bool esta_ok = true;
    for (int i = 0; i < 14; i++) {
        if (arrayGetElement(codificado, i) != ((char) codigo_esperado[i])) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE CODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    if (esta_ok) {
        vigenere_encoder_t encoder2;
        if (vigenereEncoderCreate(&encoder2, clave) < 0) {
            arrayDestroy(arreglo);
            arrayDestroy(codificado);
            return 1;
        }
        array_t *decodificado = arrayCreate(arrayGetSize(arreglo));
        if (!decodificado) {
            arrayDestroy(arreglo);
            arrayDestroy(codificado);
            return 1; 
        }
        
        for (int i = 0; i < arrayGetSize(arreglo); i++) {
            char aux = vigenereEncoderDecode(&encoder2, (unsigned char) arrayGetElement(codificado, i));
            if (arrayAdd(decodificado, &aux, 1) < 0) {
                arrayDestroy(arreglo);
                arrayDestroy(codificado);
                arrayDestroy(decodificado);
                return 1;
            }
        }
        for (int i = 0; i < 14; i++) {
            if (arrayGetElement(decodificado, i) != ((char) message[i])) {
                esta_ok = false;
                break;
            } 
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
    }   
    arrayDestroy(codificado);
    arrayDestroy(arreglo);
    return !esta_ok;
}

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("**********************PRUEBAS VIGENERE ENCODER************************\n");

    printf("**********************CREAR UN VIGENERE ENCODER***********************\n");
    resp = crear_vigenere_encoder("Key");
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR UN MENSAJE***********************\n");
    resp = cifrar_mensaje();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR Y DESCIFRAR UN MENSAJE***********************\n");
    resp = cifrar_y_descifrar_mensaje();
    printf("EL ENCODER CIFRÓ Y DESCIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    return 0;
}