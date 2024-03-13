#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <stdint.h>
#include <string.h>

#include "memory.h"

typedef struct {
	uint8_t version[16];
	uint8_t status[4];
} http_response;

http_response *http_response_construct(void *buf);

#endif
