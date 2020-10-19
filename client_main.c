#include "client.h"

// Programa principal que se encarga de dar inicio 
// a la ejecición del cliente
// Pre: recibe el host, puerto, método de codificación y clave a
// a ser utilizadas durante la ejecución del programa
// Pos: devuelve 0 en cualquier caso, en caso de error muestra 
// un mensaje por pantalla
int main(int argc, char *argv[]) {
    if ((argc < 5) || (argc > 6)) return 0;
    if (clientRun(argv[1], argv[2], argv[3], argv[4]) < 0)
        printf("Ocurrió un error al ejecutar el servidor.\n");
    return 0;
}
