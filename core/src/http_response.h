#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <stdint.h>
#include <string.h>

#include "memory.h"
#include "hash_table.h"

typedef struct {
	uint8_t version[16];
	uint8_t status[4];
	hash_table *headers;
	hash_table *body;
} http_response;

http_response *http_response_construct(const uint8_t *status, hash_table *headers, hash_table *body);
void *http_response_to_raw(http_response *response);

#endif
