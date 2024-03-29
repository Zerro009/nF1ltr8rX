#include "http_server.h"

http_response *x(http_request *request) {
	hash_table *body = tcp_scan_host("192.168.199.1", 1, 100);
	hash_table *headers = hash_table_construct();

	return http_response_construct("200", headers, body);
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

	http_server *server = http_server_construct("0.0.0.0", 8000, router);
	http_server_run(server);
}
