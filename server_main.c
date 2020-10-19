#include "server.h"

// Programa principal que se encarga de dar inicio 
// a la ejecición del servidor
// Pre: recibe el puerto, método de codificación y clave a
// a ser utilizadas durante la ejecución del programa
// Pos: devuelve 0 en cualquier caso, en caso de error muestra 
// un mensaje por pantalla
int main(int argc, char *argv[]) {
    if ((argc < 4) || (argc > 5)) return 0;
    if (serverRun(argv[1], argv[2], argv[3]) < 0)
        printf("Ocurrió un error al ejecutar el servidor.\n");
    return 0;
}
