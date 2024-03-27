#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <stdint.h>

#include "memory.h"
#include "socket.h"
#include "hash_table.h"

hash_table *tcp_scan_host(const uint8_t *host, const uint16_t from, const uint16_t to);

#endif
