#include "http_server.h"

http_response *hello(http_request *req) {
	hash_table *headers = hash_table_construct();
	hash_table_push(
		headers,
		"Content-Type",
		"application/json"
	);
	hash_table *body = hash_table_construct();
	hash_table_push(
		body,
		"22",
		"open"
	);
	http_response *response = http_response_construct("200", headers, body);

	return response;
}

int main() {
	view *v = view_construct("GET", hello);

	hash_table *router = hash_table_construct();
	hash_table_push(
		router,
		"/",
		v
	);

	http_server *server = http_server_construct("0.0.0.0", 8000, router);
	http_server_run(server);
}
