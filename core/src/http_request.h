#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "memory.h"
#include "hash_table.h"

#define METHOD_MAX_SIZE 8
#define URI_MAX_SIZE 256
#define VERSION_MAX_SIZE 16

typedef struct {
	uint8_t method[METHOD_MAX_SIZE];
	uint8_t uri[URI_MAX_SIZE];
	uint8_t version[VERSION_MAX_SIZE];
	hash_table *params;
	hash_table *headers;
	hash_table *body;
} http_request;

http_request *http_request_construct(void *buffer);
hash_table *http_request_parse_params(uint8_t *ptr);

#endif
