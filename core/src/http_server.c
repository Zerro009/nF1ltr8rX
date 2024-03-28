#include "http_server.h"

http_server *http_server_construct(const uint8_t *ipv4, uint16_t port, hash_table *router) {
	http_server *result = (http_server*) _malloc(sizeof(http_server));
	result->server = tcp_server_construct(ipv4, port);
	result->router = router;

	return result;
}

void http_server_run(http_server *server) {
	tcp_server_run(server->server, server, http_server_handle_request);
}

void *http_server_handle_request(void *superstruct, void *request) {
	http_request *req = http_request_construct(request);
	http_server *server = (http_server*) superstruct;

	// Pre-handling by middleware
	middleware_handle_request(req);

	// Checking if uri is present in server's router
	view *viewset = hash_table_at(server->router, req->uri);
	if (viewset) {
		http_response *res = viewset->func(req);

		printf("[%s]\n", res->status);

		void *result = http_response_to_raw(res);

		return result;
	}
	// If not, return 404
}
