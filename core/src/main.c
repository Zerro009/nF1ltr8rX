#include "http_server.h"
#include "hash_table.h"
#include "view.h"

void hello() {
	printf("Hello, world!\n");
}

int main() {
	view *v = view_construct("GET", hello);

	hash_table *router = hash_table_construct();
	hash_table_push(
		router,
		"/",
		v
	);

	http_server *server = http_server_construct("0.0.0.0", 8002, router);
	http_server_run(server);
}
