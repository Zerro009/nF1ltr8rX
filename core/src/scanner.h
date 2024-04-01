#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <stdint.h>
#include <time.h>
#include <netdb.h>

#include "memory.h"
#include "socket.h"
#include "hash_table.h"

#include "http_response.h"

#define ICMP_PKT_S 64

#define PING_TIMEOUT 1
#define PING_SLEEP 1

// ICMP Section (ping actually)
uint16_t icmp_checksum(void *buf, int32_t len);
struct icmphdr *icmp_construct();
int32_t icmp_ping(const uint8_t *host);

// Port scan
hash_table *tcp_scan_host(const uint8_t *host, uint16_t from, uint16_t to);
hash_table *tcp_scan_detail_port(const uint8_t *host, uint16_t port);

#endif
