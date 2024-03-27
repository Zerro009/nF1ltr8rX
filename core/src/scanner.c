#include "scanner.h"

hash_table *tcp_scan_host(const uint8_t *host, const uint16_t from, const uint16_t to) {
	hash_table *result = hash_table_construct();

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr(host);
	addr.sin_family = AF_INET;

	int16_t port = from;
	for (; port < to; port++) {
		int32_t sockfd = _socket(AF_INET, SOCK_STREAM, 0x0);
		addr.sin_port = htons(port);

		uint16_t s_port_len = snprintf(NULL, 0x0, "%d", port) + 1;
		uint8_t *s_port = (uint8_t*) _malloc(sizeof(uint8_t) * s_port_len);
		snprintf(s_port, s_port_len, "%d", port);

		if (_connect(sockfd, (struct sockaddr*) &addr, sizeof(addr)) >= 0x0) {
			hash_table_push(
				result,
				s_port,
				"open"
			);
		} else {
			hash_table_push(
				result,
				s_port,
				"closed"
			);
		}
	}

	return result;
}
