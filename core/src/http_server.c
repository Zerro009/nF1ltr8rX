#include "http_server.h"

http_server *http_server_construct(const uint8_t *ipv4, uint16_t port) {
	http_server *result = (http_server*) _malloc(sizeof(http_server));
	result->server = tcp_server_construct(ipv4, port);

	return result;
}

void http_server_run(http_server *server) {
	tcp_server_run(server->server, http_server_handle_request);
}

void *http_server_handle_request(void *request) {
	http_request *req = http_request_construct(request); 
}
