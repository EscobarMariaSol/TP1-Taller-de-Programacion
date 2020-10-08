#include "common_cesar_encoder.h"

int crear_cesar_encoder(uint32_t clave) {
    cesar_encoder_t encoder;
    if (cesarEncoderCreate(&encoder, clave) < 0) 
        return 1;
    printf("CLAVE COINCIDE: %s\n", (encoder.key == clave) ? "OK" : "FALLÓ");
    return 0;
}

int cifrar_caracter(uint32_t clave, char caracter) {
    cesar_encoder_t encoder;
    if (cesarEncoderCreate(&encoder, clave) < 0) 
        return 1;
    printf("CLAVE COINCIDE: %s\n", (encoder.key == clave) ? "OK" : "FALLÓ");
    char aux = (char)(((uint32_t)caracter) + clave);
    printf("CODIGO COINCIDE CON LO ESPERADO: %s\n",
        (cesarEncoderEncode(&encoder, caracter) == aux) ? "OK" : "FALLÓ");
    return 0;
}

int cifrar_y_descifrar_caracter(uint32_t clave, char caracter) {
    cesar_encoder_t encoder;
    if (cesarEncoderCreate(&encoder, clave) < 0) 
        return 1;
    printf("CLAVE COINCIDE: %s\n", (encoder.key == clave) ? "OK" : "FALLÓ");
    char aux = (char)(((uint32_t)caracter) + clave);
    char codigo = cesarEncoderEncode(&encoder, caracter);
    printf("CLAVE: %d, CARACTER: %c\n", clave, caracter);
    printf("CODIGO CIFRADO COINCIDE CON LO ESPERADO: %s\n",
        (codigo == aux) ? "OK" : "FALLÓ");
    printf("CLAVE: %d, CARACTER CODIFICADO: %c\n", clave, codigo);
    char decodificado = cesarEncoderDecode(&encoder, codigo);
    printf("CODIGO DESCIFRADO COINCIDE CON LO ESPERADO: %s\n",
        (decodificado == caracter) ? "OK" : "FALLÓ");
    printf("CLAVE: %d, CARACTER DECODIFICADO: %c\n", clave, decodificado);
    return 0;
}

int cifrar_y_descifrar_muchas_veces(void) {
    char *mensaje = "HOLA MUNDO";
    for (int i = 1; i <= strlen(mensaje); i++) {
        if(cifrar_y_descifrar_caracter(i, mensaje[i-1])) return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("**********************PRUEBAS CESAR ENCODER************************\n");
    printf("**********************CREAR UN CESAR ENCODER***********************\n");
    resp = crear_cesar_encoder(3);
    printf("EL ENCODER SE CREO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR UN CARACTER***********************\n");
    resp = cifrar_caracter(7, 'a');
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("**********************CIFRAR Y DESCIFRAR UN CARACTER***********************\n");
    resp = cifrar_y_descifrar_caracter(5, 'z');
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("**********************CIFRAR Y DESCIFRAR UN CARACTER MUCHAS VECES***********************\n");
    resp = cifrar_y_descifrar_muchas_veces();
    printf("EL ENCODER CIFRÓ CORRECTAMENTE: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    return 0;
}