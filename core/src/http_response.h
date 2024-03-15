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
int32_t http_response_calc_total_bytes(http_response *response);
int32_t http_response_calc_content_length(http_response *response);
void http_response_add_content_length_header(http_response *response, int32_t length);
void *http_response_to_raw(http_response *response);

#endif
