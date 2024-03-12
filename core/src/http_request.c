#include "http_request.h"

http_request *http_request_construct(void *buffer) {
	http_request *result = (http_request*) _malloc(sizeof(http_request));

	uint8_t *ptr = buffer;
	uint16_t iter = 0;
	for (; iter < METHOD_MAX_SIZE - 1; iter++) {
		if (ptr[iter] == ' ') {
			strncpy(result->method, ptr, iter);
			result->method[iter] = 0x0;
			break;
		}
	}

	ptr += iter + 1;
	iter = 0;
	for (; iter < URI_MAX_SIZE - 1; iter++) {
		if (ptr[iter] == ' ') {
			strncpy(result->uri, ptr, iter);
			result->uri[iter] = 0x0;
			break;
		}
	}

	ptr += iter + 1;
	iter = 0;
	for (; iter < VERSION_MAX_SIZE - 1; iter++) {
		if ((void *) ptr + iter == strstr(ptr, "\r\n")) {
			strncpy(result->version, ptr, iter);
			result->version[iter] = 0x0;
			break;
		}
	}

	// Headers section
	result->headers = hash_table_construct();
	return result;
}
