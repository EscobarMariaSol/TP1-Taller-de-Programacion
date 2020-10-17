#include "server.h"

int crear_servidor(void) {
    server_t servidor;
    if (serverStart(&servidor, "8080", "--method=cesar", "--key=1") < 0)
        return -1;
    serverFinish(&servidor);
    return 0;
}

int recibir_mensaje_cesar(void) {
    server_t servidor;
    if (serverStart(&servidor, "8081", "--method=cesAr", "--key=5") < 0)
        return -1;
    if (serverAcceptClient(&servidor) < 0) {
        serverFinish(&servidor);
        return -1;
    }
    if (serverReceiveMessage(&servidor) < 0) {
        serverFinish(&servidor);
        return -1;
    }
    serverFinish(&servidor);
    return 0;
}

int recibir_mensaje_vigenere() {
    server_t servidor;
    if (serverStart(&servidor, "8082", "--method=viGenere", "--key=SecureKey") < 0)
        return -1;
    if (serverAcceptClient(&servidor) < 0) {
        serverFinish(&servidor);
        return -1;
    }
    if (serverReceiveMessage(&servidor) < 0) {
        serverFinish(&servidor);
        return -1;
    }
    serverFinish(&servidor);
    return 0;
}

int recibir_mensaje_rc4() {
    server_t servidor;
    if (serverStart(&servidor, "8083", "--method=RC4", "--key=Hi") < 0)
        return -1;
    if (serverAcceptClient(&servidor) < 0) {
        serverFinish(&servidor);
        return -1;
    }
    if (serverReceiveMessage(&servidor) < 0) {
        serverFinish(&servidor);
        return -1;
    }
    serverFinish(&servidor);
    return 0;
}

int main(int argc, char *argv[]) {
    int resp;
    printf("**************Pruebas TDA Server******************************\n");

    printf("\n**************Crear nuevo Server****************************\n");
    resp = crear_servidor();
    printf("CREAR SERVIDOR FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("\n********Recibir mensaje Cesar*******************************\n");
    //resp = recibir_mensaje_cesar();
    //printf("RECIBIR MENSAJE CESAR FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n*******************Recibir mensaje Vigenere*****************\n");
    //resp = recibir_mensaje_vigenere();
    //printf("RECIBIR MENSAJE VIGENERE FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n*****************Recibir mensaje Rc4************************\n");
    resp = recibir_mensaje_rc4();
    printf("RECIBIR MENSAJE RC4 FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    return 0;
}