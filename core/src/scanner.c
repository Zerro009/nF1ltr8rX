#include "scanner.h"

unsigned short icmp_checksum(void *buf, int len) {
	unsigned short *bbuf = buf;
	unsigned int sum = 0;
	unsigned short result;

	for (sum = 0; len > 1; len -= 2) {
		sum += *bbuf++;
	}
	if (len == 1) {
		sum += *(unsigned char*)bbuf;
	}
	
	sum = (sum >> 16) + (sum & 0xFFFF);
    	sum += (sum >> 16);
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

void send_ping(int icmp_sock, struct sockaddr_in *dest_addr) {
	struct icmphdr icmp;
	char packet[ICMP_PKT_S];

	bzero(packet, ICMP_PKT_S);

	icmp.type = ICMP_ECHO;
	icmp.code = 0;
	icmp.un.echo.id = getpid();
	icmp.un.echo.sequence = 0;
	icmp.checksum = 0;
	icmp.checksum = icmp_checksum(&icmp, sizeof(icmp));

	memcpy(packet, &icmp, sizeof(icmp));

	sendto(icmp_sock, packet, sizeof(packet), 0, (struct sockaddr*)dest_addr, sizeof(*dest_addr));
}

int32_t icmp_ping(const uint8_t *host) {
	int icmp_sock = _socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	struct sockaddr_in dest_addr;
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = 0;
	dest_addr.sin_addr.s_addr = inet_addr(host);

	send_ping(icmp_sock, &dest_addr);

        struct sockaddr_in recv_addr;
       	socklen_t addr_len = sizeof(recv_addr);
        char recv_msg[ICMP_PKT_S];
	bzero(recv_msg, ICMP_PKT_S);

	// Setting timeout
	struct timeval timeout = {PING_TIMEOUT, 0x0};
	setsockopt(icmp_sock, SOL_SOCKET, SO_RCVTIMEO, (const uint8_t*)&timeout, sizeof(timeout));

	int32_t bytes;
	if (bytes = recvfrom(icmp_sock, recv_msg, sizeof(recv_msg), 0, (struct sockaddr*)&recv_addr, &addr_len) > 0) {
       		char *recv_ip = inet_ntoa(recv_addr.sin_addr);
        	if (strcmp(recv_ip, host) == 0x0) {
			_close(icmp_sock);
			return 0x1;
            	}
		_close(icmp_sock);
		return 0x0;
	}
	_close(icmp_sock);
	return 0x0;
}

hash_table *tcp_scan_host(const uint8_t *host, uint16_t from, uint16_t to) {
	hash_table *result = hash_table_construct();

	struct sockaddr_in addr;
	addr.sin_addr.s_addr = inet_addr(host);
	addr.sin_family = AF_INET;

	int16_t port = from;
	for (; port <= to; port++) {
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
