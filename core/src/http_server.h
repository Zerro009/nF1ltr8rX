#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include "tcp_server.h"
#include "http_request.h"
#include "http_response.h"
#include "view.h"

typedef struct {
	tcp_server *server;
	hash_table *router;
} http_server;

http_server *http_server_construct(const uint8_t *ipv4, uint16_t port, hash_table *router);
void http_server_run(http_server *server);

// Actually the func that manages incoming data and returns response
void *http_server_handle_request(void *superstruct, void *request);

// Middleware to handle incoming request

#endif
