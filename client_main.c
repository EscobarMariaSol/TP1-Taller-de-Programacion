#include "client.h"

int main(int argc, char *argv[]) {
    if ((argc < 5) || (argc > 6)) return 0;
    return clientRun(argv[1], argv[2], argv[3], argv[4]);
}
