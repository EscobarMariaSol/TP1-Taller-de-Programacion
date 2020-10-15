#include "client.h"

int crear_cliente(void) {
    client_t cliente;
    if (clientStart(&cliente, "localhost", "8080", "--method=cesar", "--key=1") < 0)
        return -1;
    clientFinish(&cliente);
    return 0;
}

int enviar_mensaje_cesar(void) {
    client_t cliente;
    if (clientStart(&cliente, "localhost", "8081", "--method=cesar", "--key=5") < 0)
        return -1;
    if (clientSendMessage(&cliente) < 0) return -1;
    clientFinish(&cliente);
    return 0;
}

int enviar_mensaje_vigenere() {
    client_t cliente;
    if (clientStart(&cliente, "localhost", "8082", "--method=vigenere", "--key=SecureKey") < 0)
        return -1;
    if (clientSendMessage(&cliente) < 0) return -1;
    clientFinish(&cliente);
    return 0;
}

int enviar_mensaje_rc4() {
    client_t cliente;
    if (clientStart(&cliente, "localhost", "8083", "--method=rc4", "--key=Key") < 0)
        return -1;
    if (clientSendMessage(&cliente) < 0) return -1;
    clientFinish(&cliente);
    return 0;
}

int main(int argc, char *argv[]) {
    int resp;
    printf("**************Pruebas TDA Client******************************\n");

    printf("\n**************Crear nuevo Client****************************\n");
    resp = crear_cliente();
    printf("CREAR CLIENTE FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");

    printf("\n********Enviar mensaje Cesar desde Client*******************\n");
    resp = enviar_mensaje_cesar();
    printf("ENVIAR MENSAJE CESAR FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n************Enviar mensaje Vigenere desde Client************\n");
    resp = enviar_mensaje_vigenere();
    printf("ENVIAR MENSAJE VIGENERE FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    printf("\n**************Enviar mensaje Rc4 desde Client***************\n");
    resp = enviar_mensaje_rc4();
    printf("ENVIAR MENSAJE RC4 FUNCIONÓ: %s\n", (resp == 0) ? "OK" : "FALLÓ");
    
    return 0;
}