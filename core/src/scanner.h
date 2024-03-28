#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <stdint.h>
#include <time.h>

#include "memory.h"
#include "socket.h"
#include "hash_table.h"

#define ICMP_PKT_S 64

#define PING_TIMEOUT 2
#define PING_SLEEP 1

// ICMP Section
uint16_t icmp_checksum(uint16_t *addr, int32_t len);
struct icmphdr *icmp_construct();
int32_t icmp_send(int32_t sockfd, struct icmphdr *pkt, struct sockaddr_in *addr);
int32_t icmp_recv(int32_t sockfd, struct icmphdr *pkt, struct sockaddr_in *addr);
int32_t icmp_ping(const uint8_t *host);

// Recon
hash_table *tcp_scan_host(const uint8_t *host, uint16_t from, uint16_t to);

#endif
