#include "tcp_server.h"

tcp_server *tcp_server_construct(const uint8_t *ipv4, int16_t port) {
	tcp_server *result = (tcp_server*) _malloc(sizeof(tcp_server));

	result->addr.sin_port = htons(port);
	result->addr.sin_family = AF_INET;
	result->addr.sin_addr.s_addr = inet_addr(ipv4);

	result->socket = _socket(AF_INET, SOCK_STREAM, 0x0);
	_bind(result->socket, (struct sockaddr*)&result->addr, sizeof(result->addr));

	return result;
}

void tcp_server_run(tcp_server *server, void *(*func)(void *buf)) {
	_listen(server->socket, 16);
	for (;;) {
		int32_t addrl = sizeof(server->client.addr);
		server->client.socket = _accept(server->socket, &server->client.addr, &addrl);

		int32_t pid = fork();
		if (pid == 0x0) {
			_close(server->socket);

			_recv(server->client.socket, server->client.buffer, BUFSIZE, 0x0);
			func(server->client.buffer);

			exit(0x0);
		} 
		_close(server->client.socket);

		do {
			pid = wait4(-1, NULL, WNOHANG, NULL);
		} while (pid > 0x0);
	}
}
