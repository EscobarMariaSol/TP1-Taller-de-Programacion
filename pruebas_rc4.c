#include "common_rc4_encoder.h"

int crear_rc4_encoder(char *clave) {
    rc4_encoder_t encoder;
    if (rc4EncoderCreate(&encoder, (unsigned char*)clave) < 0) 
        return 1;
    printf("RC4 SE CREÓ CORRECTAMENTE: %s\n",
        ((encoder.stream != NULL) && (encoder.i == 0) && (encoder.j == 0))? "OK" : "FALLÓ");
    return 0;
}

int cifrar_mensaje(void) {
    char *clave = "Key";
    char *message = "Plaintext";
    uint32_t codigo_esperado[] = {0xBB, 0xF3, 0x16, 0xE8, 0xD9, 0x40, 0xAF, 0x0A, 0xD3};
    rc4_encoder_t encoder;
    
    if (rc4EncoderCreate(&encoder, (unsigned char*)(clave)) < 0) return 1;
    printf("RC4 SE CREÓ CORRECTAMENTE: %s\n",
        ((encoder.stream != NULL) && (encoder.i == 0) && (encoder.j == 0))? "OK" : "FALLÓ");
    
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    
    array_t *codificado = arrayCreate(arrayGetSize(arreglo));
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1; 
    }
    
    for (int i = 0; i < arrayGetSize(arreglo); i++) {
        char aux = rc4EncoderEncode(&encoder, (unsigned char) arrayGetElement(arreglo, i));
        printf("CODIGO ESPERADO: %x, CODIGO RECIBIDO: %x\n", codigo_esperado[i], aux);
        if (arrayAdd(codificado, &aux, 1) < 0) {
            arrayDestroy(arreglo);
            arrayDestroy(codificado);
            return 1;
        }
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

int cifrar_y_descifrar_mensaje(void) {
    char *clave = "Secret";
    char *message = "Attack at dawn";
    uint32_t codigo_esperado[] = {0x45, 0xA0, 0x1F,
                        0x64, 0x5F, 0xC3, 0x5B, 0x38, 0x35, 0x52, 0x54, 0x4B, 0x9B, 0xF5};
    rc4_encoder_t encoder;
    if (rc4EncoderCreate(&encoder, (unsigned char*)(clave)) < 0) 
        return 1;
    printf("RC4 SE CREÓ CORRECTAMENTE: %s\n",
        ((encoder.stream != NULL) && (encoder.i == 0) && (encoder.j == 0))? "OK" : "FALLÓ");
    array_t *arreglo = arrayCreate(strlen(message));
    if (!arreglo) return 1;
    if (arrayAdd(arreglo, message, strlen(message)) < 0) {
        arrayDestroy(arreglo);
        return 1;
    }
    array_t *codificado = arrayCreate(arrayGetSize(arreglo));
    if (!codificado) {
        arrayDestroy(arreglo);
        return 1; 
    }
    
    for (int i = 0; i < arrayGetSize(arreglo); i++) {
        char aux = rc4EncoderEncode(&encoder, arrayGetElement(arreglo, i));
        if (arrayAdd(codificado, &aux, 1) < 0) {
            arrayDestroy(arreglo);
            arrayDestroy(codificado);
            return 1;
        }
    }

    bool esta_ok = true;
    for (int i = 0; i < 9; i++) {
        if (arrayGetElement(codificado, i) != ((char) codigo_esperado[i])) {
            return 1;
        } 
    }
    printf("MENSAJE CODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    
    rc4_encoder_t encoder2;
    if (rc4EncoderCreate(&encoder2, (unsigned char*)(clave)) < 0) 
        return 1;
    array_t *decodificado = arrayCreate(arrayGetSize(arreglo));
    if (!decodificado) {
        arrayDestroy(arreglo);
        return 1; 
    }
    
    for (int i = 0; i < arrayGetSize(codificado); i++) {
        unsigned char aux = rc4EncoderEncode(&encoder2, arrayGetElement(codificado, i));
        if (arrayAdd(decodificado, (char*) &aux, 1) < 0) {
            arrayDestroy(arreglo);
            arrayDestroy(codificado);
            arrayDestroy(decodificado);
            return 1;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (arrayGetElement(decodificado, i) != ((char) message[i])) {
            esta_ok = false;
            break;
        } 
    }
    printf("MENSAJE DECODIFICADO COINCIDE CON LO ESPERADO: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    arrayDestroy(decodificado);
    arrayDestroy(codificado);
    arrayDestroy(arreglo);
    return !esta_ok;
}

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("**********************PRUEBAS RC4 ENCODER************************\n");

    printf("**********************CREAR UN RC4 ENCODER***********************\n");
    resp = crear_rc4_encoder("Key");
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR UN MENSAJE***********************\n");
    resp = cifrar_mensaje();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR Y DESCIFRAR UN MENSAJE***********************\n");
    resp = cifrar_y_descifrar_mensaje();
    printf("EL ENCODER CIFRÓ Y DESCIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    /*printf("**********************CIFRAR Y DESCIFRAR UN CARACTER MUCHAS VECES***********************\n");
    resp = cifrar_y_descifrar_muchas_veces();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");*/
    return 0;
}