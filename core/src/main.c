#include "http_server.h"

http_response *x(http_request *request) {
	uint8_t *host = hash_table_at(request->params, "host");
	uint16_t from = atoi(hash_table_at(request->params, "from"));
	uint16_t to = atoi(hash_table_at(request->params, "to"));

	hash_table *body = tcp_scan_host(host, from, to);
	hash_table *headers = hash_table_construct();
	return http_response_construct("200", headers, body);
}

http_response *p(http_request *request) {
	uint8_t *host = hash_table_at(request->params, "host");

	int32_t result = icmp_ping(host);

	hash_table *body = hash_table_construct();
	if (result == 0x1) {
		hash_table_push(
			body,
			host,
			"up"
		);
		return http_response_construct("200", NULL, body);
	} else {
		hash_table_push(
			body,
			host,
			"down"
		);
		return http_response_construct("200", NULL, body);
	}
}	

int main() {
	// Check for root privileges
	if (geteuid() != 0x0) {
		fprintf(stderr, "Some funcs require root privileges!\n");
	}

	hash_table *router = hash_table_construct();

	hash_table_push(
		router,
		"/scanner/tcp/",
		view_construct("GET", x)
	);


	hash_table_push(
		router,
		"/ping/",
		view_construct("GET", p)
	);

	http_server *server = http_server_construct("0.0.0.0", 8000, router);
	http_server_run(server);
}
