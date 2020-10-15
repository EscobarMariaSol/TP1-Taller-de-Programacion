#include "common_input_output_handler.h"

int crear_input_output_handler(char *ruta) {
    input_output_handler_t handler;
    if (inputOutputHandlerCreate(&handler, ruta) < 0) return -1;
    else if ((ruta == NULL) && (handler.file != stdin)) {
        inputOutputHandlerDestroy(&handler); 
        return -1;
    }
    inputOutputHandlerDestroy(&handler);
    return 0;
}

int usar_input_handler(char *ruta, char *contenido_esperado) {
    input_output_handler_t handler;
    
    if (inputOutputHandlerCreate(&handler, ruta) < 0) return -1;
    if ((ruta == NULL) && (handler.file != stdin)) return -1;

    array_t *array_contenido = inputOutputHandlerGetMessage(&handler);
    if (!array_contenido) {
        inputOutputHandlerDestroy(&handler);
        return -1;
    }
    bool esta_ok = true;
    for (int i = 0; i < arrayGetSize(array_contenido); i++){
        if (arrayGetElement(array_contenido, i) != (unsigned char) contenido_esperado[i]) {
            esta_ok = false;
            break;
        }
    }
    printf("MENSAJE RECIBIDO OK: %s\n", (esta_ok) ? "OK" : "FALLÓ");
    arrayDestroy(array_contenido);
    inputOutputHandlerDestroy(&handler);
    return !esta_ok;
}

int usar_output_handler(char *ruta, char *contenido) {
    input_output_handler_t handler;
    
    if (inputOutputHandlerCreate(&handler, ruta) < 0) return -1;
    if ((ruta == NULL) && (handler.file != stdin)) return -1;

    array_t *array_contenido = arrayCreate(strlen(contenido));
    if (!array_contenido) {
        inputOutputHandlerDestroy(&handler);
        return -1;
    }
    if (arrayAdd(array_contenido, (unsigned char*) contenido, strlen(contenido)) < 0) {
        inputOutputHandlerDestroy(&handler);
        arrayDestroy(array_contenido);
        return -1;
    }
    if (inputOutputHandlerSetMessage(&handler, array_contenido) < 0) {
        inputOutputHandlerDestroy(&handler);
        arrayDestroy(array_contenido);
        return -1;
    }
    arrayDestroy(array_contenido);
    inputOutputHandlerDestroy(&handler);
    return 0;
}

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("***************PRUEBAS HANDLER I/O****************\n");

    printf("\n****************CREAR HANDLER*****************************\n");
    resp = crear_input_output_handler("Pruebas/prueba_1.txt");
    printf("SE CREO EL MANEJADOR DE ARCHIVOS: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n***********CREAR HANDLER SIN RUTA*************\n");
    resp = crear_input_output_handler(NULL);
    printf("SE CREO EL MANEJADOR DE ARCHIVOS QUE USA STDIN: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("\n***CREAR MANEJADOR DE ARCHIVOS CON RUTA INEXISTENETE FALLA**\n");
    resp = crear_input_output_handler("CUALquiera");
    printf("NO SE CREO EL MANEJADOR DE ARCHIVOS: %s\n", (resp < 0) ? "OK" : "FALLÓ");

    printf("\n****************OBTENER CONTENIDO DEL ARCHIVO***************\n");
    resp = usar_input_handler("Pruebas/prueba_2.txt", "HOLA\nmundo!");
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE TODO EL TEXTO DEL ARCHIVO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n********OBTENER CONTENIDO DE UN ARCHIVO VACIO***************\n");
    resp = usar_input_handler("Pruebas/prueba_3.txt", "");
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE UN STRING VACIO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n*****OBTENER CONTENIDO DE UN ARCHIVO CON SALTOS DE LINEA****\n");
    resp = usar_input_handler("Pruebas/prueba_4.txt", "\n\n");
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE EL CONTENIDO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n*****OBTENER CONTENIDO DE UN ARCHIVO MUY LARGO**************\n");
    char *array_contenido = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore \nmagna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo \nconsequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla \npariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id \nest laborum.";
    resp = usar_input_handler("Pruebas/prueba_1.txt", array_contenido);
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE EL CONTENIDO: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("\n********ESCRIBIR UN MENSAJE POR SALIDA STDOUT***************\n");
    char *contenido = "HOLA";
    resp = usar_output_handler(NULL, contenido);
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE EL CONTENIDO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    return 0;
}