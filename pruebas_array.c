#include "common_array.h"

#define CHICO 8
#define MEDIO 160
#define GRANDE 1000

int crear_arreglo_dinamico(size_t tamanio) {
    array_t* arreglo = arrayCreate(tamanio);
    if(!arreglo) return 1;
    printf("TAMAÑO: %zu\n", arrayGetSize(arreglo));
    printf("POSICIÓN: %d\n", arreglo->pos);
    arrayDestroy(arreglo);
    return 0;
}

int copiar_en_arreglo(char *mensaje) {
    array_t* arreglo = arrayCreate(0);
    if(!arreglo) return 1;
    printf("TAMAÑO INICIAL: %zu\n", arrayGetSize(arreglo));
    printf("POSICIÓN: %d\n", arreglo->pos);
    arrayAdd(arreglo, mensaje, strlen(mensaje));
    printf("TAMAÑO FINAL: %zu\n", arrayGetSize(arreglo));
    printf("POSICIÓN: %d\n", arreglo->pos);
    if (arrayGetSize(arreglo) > 0) printf("MENSAJE: %s\n", (char*)arrayGetContent(arreglo));
    arrayDestroy(arreglo);
    return 0;
}

int copiar_en_arreglo_muchas_veces(char *mensaje) {
    array_t* arreglo = arrayCreate(0);
    if (!arreglo) return 1;
    printf("TAMAÑO INICIAL: %zu\n", arrayGetSize(arreglo));
    printf("POSICIÓN: %d\n", arreglo->pos);
    for (int i = 0; i < 12; i++) {
        arrayAdd(arreglo, mensaje, strlen(mensaje));
        printf("TAMAÑO ACTUAL: %zu\n", arrayGetSize(arreglo));
        printf("POSICIÓN: %d\n", arreglo->pos);
    }
    printf("MENSAJE: %s\n", (char*)arrayGetContent(arreglo));
    arrayDestroy(arreglo);
    return 0;
}

int copiar_en_arreglo_y_limpiar(char *mensaje) {
    array_t* arreglo = arrayCreate(0);
    if (!arreglo) return 1;
    printf("TAMAÑO INICIAL: %zu\n", arrayGetSize(arreglo));
    printf("POSICIÓN: %d\n", arreglo->pos);
    arrayAdd(arreglo, mensaje, strlen(mensaje));
    printf("MENSAJE COPIADO: %s\n", (char*)arrayGetContent(arreglo));
    if (arrayClear(arreglo)) return 1;
    printf("TAMAÑO FINAL: %zu\n", arrayGetSize(arreglo));
    printf("POSICIÓN: %d\n", arreglo->pos);
    arrayDestroy(arreglo);
    return 0;
}

int copiar_en_arreglo_y_limpiar_muchas_veces(char *mensaje) {
    array_t* arreglo = arrayCreate(0);
    if (!arreglo) return 1;
    for (int i = 0; i < 5; i++) {
        printf("TAMAÑO INICIAL: %zu\n", arrayGetSize(arreglo));
        printf("POSICIÓN: %d\n", arreglo->pos);
        arrayAdd(arreglo, mensaje, strlen(mensaje));
        printf("MENSAJE COPIADO: %s\n", (char*)arrayGetContent(arreglo));
        printf("TAMAÑO ACTUAL: %zu\n", arrayGetSize(arreglo));
        printf("POSICIÓN: %d\n", arreglo->pos);
        if (arrayClear(arreglo)) return 1;
    }
    arrayDestroy(arreglo);
    return 0;
}

int copiar_en_arreglo_y_recorrer(char *mensaje) {
    array_t* arreglo = arrayCreate(0);
    if(!arreglo) return 1;
    arrayAdd(arreglo, mensaje, strlen(mensaje));
    printf("TAMAÑO FINAL: %zu\n", arrayGetSize(arreglo));
    printf("POSICIÓN: %d\n", arreglo->pos);
    if (arrayGetSize(arreglo) > 0) printf("MENSAJE: %s\n", (char*)arrayGetContent(arreglo));
    for (int i = 0; i < arrayGetSize(arreglo); i++) {
        printf("POSICIÓN: %d CARACTER: %c\n", i, arrayGetElement(arreglo, i));
    }
    arrayDestroy(arreglo);
    return 0;
}

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("*********************PRUEBAS ARREGLO DINÁMICO**********************\n");
    printf("*********************CREAR ARREGLO DE TAMAÑO 0*********************\n");
    resp = crear_arreglo_dinamico(0);
    printf("RESPUESTA CREAR TAMAÑO 0: %d\n", resp);
    printf("*********************CREAR UN ARREGLO DE TAMAÑO 8******************\n");
    resp = crear_arreglo_dinamico(CHICO);
    printf("RESPUESTA CREAR TAMAÑO %d: %d\n", CHICO, resp);
    printf("********************CREAR UN ARREGLO DE TAMAÑO 160*****************\n");
    resp = crear_arreglo_dinamico(MEDIO);
    printf("RESPUESTA CREAR TAMAÑO %d: %d\n", MEDIO, resp);
    printf("*********************CREAR UN ARREGLO DE TAMAÑO 1000***************\n");
    resp = crear_arreglo_dinamico(GRANDE);
    printf("RESPUESTA CREAR TAMAÑO %d: %d\n", GRANDE, resp);
    printf("********************COPIAR UN MENSAJE VACIO************************\n");
    resp = copiar_en_arreglo("");
    printf("RESPUESTA COPIAR NADA: %d\n", resp);
    printf("***********************COPIAR UN MENSAJE CORTO*********************\n");
    resp = copiar_en_arreglo("Hola Mundo!");
    printf("RESPUESTA COPIAR ALGO CORTO: %d\n", resp);
    printf("************************COPIAR UN MENSAJE LARGO********************\n");
    resp = copiar_en_arreglo("Lorem ipsum dolor sit amet, consectetur adipiscing elit");
    printf("RESPUESTA COPIAR ALGO LARGO: %d\n", resp);
    printf("*********************COPIAR UN MENSAJE MUY LARGO*******************\n");
    resp = copiar_en_arreglo("Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem.");
    printf("RESPUESTA COPIAR ALGO MUY LARGO: %d\n", resp);
    printf("*********************COPIAR MUCHOS MENSAJES************************\n");
    resp = copiar_en_arreglo_muchas_veces("HOLA_");
    printf("RESPUESTA COPIAR ALGO MUY LARGO EN MUCHAS REPETICIONES: %d\n", resp);
    printf("**************************COPIAR Y LIMPIAR*************************\n");
    resp = copiar_en_arreglo_y_limpiar("Hola Mundo!");
    printf("RESPUESTA COPIAR Y LIMPIAR: %d\n", resp);
    printf("*********************COPIAR Y LIMPIAR MUCHAS VECES*****************\n");
    resp = copiar_en_arreglo_y_limpiar_muchas_veces("Hola Mundo!");
    printf("RESPUESTA COPIAR Y LIMPIAR MUCHAS VECES: %d\n", resp);
    printf("*********************COPIAR EN ARREGLO Y RECORRER******************\n");
    resp = copiar_en_arreglo_y_recorrer("Hello!");
    printf("RESPUESTA COPIAR en arreglo y recorrer: %d\n", resp);
    return resp;
}