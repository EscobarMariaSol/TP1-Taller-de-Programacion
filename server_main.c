#include "server.h"

int main(int argc, char *argv[]) {
    if((argc < 4) || (argc > 5)) return 0;
    return serverRun(argv[1], argv[2], argv[3]);
}