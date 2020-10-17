#include "server.h"

int main(int argc, char *argv[]) {
    if((argc < 4) || (argc > 5)) return 0;
    if (serverRun(argv[1], argv[2], argv[3]) < 0)
        printf("Ocurrió un error al ejecutar el servidor.\n");
    return 0;
}