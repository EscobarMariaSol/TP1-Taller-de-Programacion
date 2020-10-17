#define _POSIX_C_SOURCE 201112L
#include "common_socket.h"

/************************Funciones Auxiliares*********************************/

/************************Auxiliares Comúnes***********************************/
void initAddrinfo(struct addrinfo *hints, int flag) {
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;       
	hints->ai_socktype = SOCK_STREAM; 
	hints->ai_flags = flag;
	hints->ai_protocol = 0; 
}

int callGetAddrInfo(socket_t* socket, struct addrinfo **addr, 
					const char* host, const char* port, int flag) {
	struct addrinfo hints;
	struct addrinfo *address;
	initAddrinfo(&hints, flag);
	if (getaddrinfo(host, port, &hints, &address) != 0) return -1;
	*addr = address;
	return 0;
}

/************************Auxiliares Servidor**********************************/

int activeReuseAddr(socket_t* self) {
	int val = 1;
	return setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

int setFD(socket_t *self, struct addrinfo *addrs) {
	int skt_fd;
	skt_fd = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol);
	if (skt_fd < 0) return -1;
	self->fd = skt_fd;
	if (activeReuseAddr(self) < 0) return -1;
	return 0;
}

int setAddrInfo(socket_t* self, struct addrinfo **addr, 
				const char* port, int flag) {
	if (callGetAddrInfo(self, addr, NULL, port, flag) < 0) 
		return -1;
	return 0;
}

int bindAndListen(socket_t* self, struct addrinfo *addr) {
	int fd = self->fd;
	struct addrinfo *aux_addr; 
	for (aux_addr = addr; aux_addr; aux_addr = aux_addr->ai_next)
		if (bind(fd, aux_addr->ai_addr, aux_addr->ai_addrlen) > -1) break;
	if (!aux_addr) return -1;
	if (listen(self->fd, 1) < 0) return -1;
	return 0;
}

int initServerSocket(socket_t* self, const char* host, const char* port) {
	struct addrinfo *addr;
	if (setAddrInfo(self, &addr, port, AI_PASSIVE) < 0) return -1;
	if ((setFD(self, addr) < 0) || (bindAndListen(self, addr) < 0)) {
		close(self->fd);
		freeaddrinfo(addr);
		return -1;
	}
	freeaddrinfo(addr);
	return 0;
}

/************************Auxiliares Cliente***********************************/

int findConnection(struct addrinfo *addrs, int *skt_fd) {
	struct addrinfo *aux;
	for (aux = addrs; aux; aux = aux->ai_next) {
		*skt_fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
		if (*skt_fd < 0) continue;
		if (connect(*skt_fd, aux->ai_addr, aux->ai_addrlen) > -1) break;
		else 
			close(*skt_fd);
	}
	if (!aux) return -1;
	return 0;
}

int connectAddress(socket_t* client_socket, struct addrinfo *addr) {
	int socket_fd;
	if (findConnection(addr, &socket_fd) < 0) return -1;
	client_socket->fd = socket_fd;
	return 0;
}

int initClientSocket(socket_t *client_socket, 
						const char *host, const char *port) {
	struct addrinfo *addr;
	if (!host && !port) return 0; //socket aceptador
	if (callGetAddrInfo(client_socket, &addr, host, port, 0) < 0) return -1;
	if (connectAddress(client_socket, addr) < 0) {
		freeaddrinfo(addr);
		return -1; 
	}
	freeaddrinfo(addr);
	return 0;
}

/************************Primitivas de TDA Socket*****************************/

int socketCreate(socket_t* socket, const char* host, 
					const char* port, uint16_t type) {
    memset(socket, 0, sizeof(socket_t));
    if (type == 1) {
		if (initServerSocket(socket, host, port) < 0) return -1;
	} else if (type == 0) {
		if (initClientSocket(socket, host, port) < 0) return -1;
	} else { // cualquier otro tipo => tipo incorrecto
		return -1; 
	}
	return 0;
}

int socketAccept(socket_t* self, socket_t* accept_socket) {
	int fd = accept(self->fd, NULL, NULL);
	if (fd < 0) return -1;
	if (socketCreate(accept_socket, NULL, NULL, 0) < 0) {
		close(fd);
		return -1;
	}
    accept_socket->fd = fd;
    return 0;
}

int socketSend(socket_t *self, const unsigned char *buffer, size_t size) {
	int total = 0, sent = 0;
	do {
		sent = send(self->fd, &buffer[total], size-total, MSG_NOSIGNAL);
		if (sent > 0)  total += sent;
	} while ((sent > 0) && (total < size));
	if (sent <= 0)  return -1;
	return total;
}

int socketRecv(socket_t* self, unsigned char *buffer, size_t size) {
	int total = 0, recived = 0;
	do {
		recived = recv(self->fd, (buffer + total), (size-total), 0);
		if (recived > 0) total += recived;
	} while (recived == (size - total));
    if (recived <= 0) return -1;
	return total;
}

void socketDestroy(socket_t* self) {
	if (self->fd) {
		shutdown(self->fd, SHUT_RDWR);
		close(self->fd);
	}
}
