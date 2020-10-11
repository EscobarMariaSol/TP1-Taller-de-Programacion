#include "common_file_handler.h"

int crear_file_handler(char *ruta) {
    file_handler_t handler;
    if (fileHandlerCreate(&handler, ruta) < 0) return -1;
    if ((ruta == NULL) && (handler.file != stdin)) return -1;
    fileHandlerDestroy(&handler);
    return 0;
}

int usar_file_handler(char *ruta, char *contenido_esperado) {
    file_handler_t handler;
    
    if (fileHandlerCreate(&handler, ruta) < 0) return -1;
    if ((ruta == NULL) && (handler.file != stdin)) return -1;

    array_t *contenido = fileHandlerGetFileContent(&handler);
    if (!contenido) {
        printf("CONTENIDO: Falla\n");
        fileHandlerDestroy(&handler);
        return -1;
    }
    if (strcmp(contenido_esperado, arrayGetContent(contenido)) != 0) {
        fileHandlerDestroy(&handler);
        arrayDestroy(contenido);
        return -1;
    }
    arrayDestroy(contenido);
    fileHandlerDestroy(&handler);
    return 0;
}

int main(int argc, char *argv[]) {
    int resp = 1;
    printf("****************PRUEBAS MANEJADOR DE ARCHIVOS***************\n");

    printf("\n****************CREAR MANEJADOR DE ARCHIVOS*****************\n");
    resp = crear_file_handler("prueba_1.txt");
    printf("SE CREO EL MANEJADOR DE ARCHIVOS: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n***********CREAR MANEJADOR DE ARCHIVOS SIN RUTA**************\n");
    resp = crear_file_handler(NULL);
    printf("SE CREO EL MANEJADOR DE ARCHIVOS QUE USA STDIN: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("\n***CREAR MANEJADOR DE ARCHIVOS CON RUTA INEXISTENETE FALLA***\n");
    resp = crear_file_handler("CUALquiera");
    printf("NO SE CREO EL MANEJADOR DE ARCHIVOS: %s\n", (resp < 0) ? "OK" : "FALLÓ");

    printf("\n****************OBTENER CONTENIDO DEL ARCHIVO****************\n");
    resp = usar_file_handler("prueba_2.txt", "HOLA\nmundo!");
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE TODO EL TEXTO DEL ARCHIVO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n********OBTENER CONTENIDO DE UN ARCHIVO VACIO****************\n");
    resp = usar_file_handler("prueba_3.txt", "");
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE UN STRING VACIO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n*****OBTENER CONTENIDO DE UN ARCHIVO CON SALTOS DE LINEA*****\n");
    resp = usar_file_handler("prueba_4.txt", "\n\n");
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE EL CONTENIDO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n*****OBTENER CONTENIDO DE UN ARCHIVO MUY LARGO*****\n");
    char *contenido = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore \nmagna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo \nconsequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla \npariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id \nest laborum.";
    resp = usar_file_handler("prueba_1.txt", contenido);
    printf("EL MANEJADOR DE ARCHIVOS DEVUELVE EL CONTENIDO: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    return 0;
}