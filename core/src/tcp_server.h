#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <signal.h>
#include <string.h>

#include "memory.h"
#include "socket.h"

#define BUFSIZE 4096

typedef struct {
	int32_t socket;
	struct sockaddr addr;
	uint8_t buffer[BUFSIZE];
} tcp_client;

typedef struct {
	int32_t socket;
	struct sockaddr_in addr;
	tcp_client client;
} tcp_server;

tcp_server *tcp_server_construct(const uint8_t *ipv4, int16_t port);
void tcp_server_run(tcp_server *server, void *superstruct, void *(*func)(void *superstruct, void *buf));

// Handle SIGINT
static void sigintHandler(int32_t sigint);

#endif
