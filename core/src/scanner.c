#include "scanner.h"

uint16_t icmp_checksum(uint16_t *addr, int32_t len) {
	uint16_t result;
	int32_t sum = 0x0;
	uint16_t *w = addr;
	int32_t nleft = len;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	if (nleft == 1) {
		*(uint8_t*) (&result) = *(uint8_t*) w;
		sum += result;
	}

	sum = (sum >> 0x10) + (sum & 0xFFFF);
	sum += (sum >> 0x10);
	result = ~sum;

	return result;
}

struct icmphdr *icmp_construct() {
	uint8_t pkt[ICMP_PKT_S];
	struct icmphdr *icmp = (struct icmphdr *) pkt;
	
	icmp->type = ICMP_ECHO;
	icmp->code = 0x0;
	icmp->un.echo.sequence = 0x0;
	icmp->un.echo.id = 0x0;
	icmp->checksum = 0x0;
	memset(pkt + sizeof(struct icmphdr), 0xa5, ICMP_PKT_S - sizeof(struct icmphdr));

	icmp->checksum = icmp_checksum((uint16_t *) icmp, ICMP_PKT_S);

	return icmp;
}

int32_t icmp_send(int32_t sockfd, struct icmphdr *pkt, struct sockaddr_in *addr) {
	return sendto(sockfd, pkt, ICMP_PKT_S, 0x0, (struct sockaddr *)addr, sizeof(struct sockaddr_in));
}

int32_t icmp_recv(int32_t sockfd, struct icmphdr *pkt, struct sockaddr_in *addr) {
	int32_t addr_len = sizeof(struct sockaddr_in);
	return recvfrom(sockfd, pkt, ICMP_PKT_S, 0x0, (struct sockaddr*)addr, &addr_len);
}

int32_t icmp_ping(const uint8_t *host) {
	int32_t sockfd = _socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	struct icmphdr *pkt = icmp_construct();

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host);

	int32_t bytes_sent = icmp_send(sockfd, pkt, &addr);

	time_t start, current;
	time(&start);

	do {
		time(&current);
		int32_t bytes = icmp_recv(sockfd, pkt, &addr);
		if (bytes > 0x0) {
			printf("\n%d\n bytes received!\n", bytes);
			break;
		}
	} while (current - start <= PING_TIMEOUT);

	return bytes_sent;
}

hash_table *tcp_scan_host(const uint8_t *host, uint16_t from, uint16_t to) {
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
