#include "http_server.h"
#include "hash_table.h"

int main() {
	http_server *server = http_server_construct("0.0.0.0", 8000);
	http_server_run(server);
}
