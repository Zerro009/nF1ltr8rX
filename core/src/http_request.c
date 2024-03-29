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
	int8_t params = 0x0;
	for (; iter < URI_MAX_SIZE - 1; iter++) {
		if ((ptr[iter] == ' ') || ptr[iter] == '?') {
			if (ptr[iter] == '?') {
				params = 0x1;
			}
			strncpy(result->uri, ptr, iter);
			result->uri[iter] = 0x0;
			break;
		}
	}

	ptr += iter + 1;
	iter = 0;
	uint8_t *params_ptr = ptr;
	if (params) {
		result->params = http_request_parse_params(ptr);
		ptr = strchr(ptr, ' ') + 0x1;
		iter = 0;
	}

	for (; iter < VERSION_MAX_SIZE - 1; iter++) {
		if ((void *) ptr + iter == strstr(ptr, "\r\n")) {
			strncpy(result->version, ptr, iter);
			result->version[iter] = 0x0;
			break;
		}
	}

	// Headers section
	result->headers = hash_table_construct();
	
	// Body section
	result->body = hash_table_construct();

	return result;
}

hash_table *http_request_parse_params(uint8_t *ptr) {
	hash_table *result = hash_table_construct();

	uint8_t *params_end = strchr(ptr, ' ');
	uint8_t *key, *delimiter, *value;
	int32_t length = 0x0;
	
	for (int32_t i = 0x0; ptr + i < params_end; i++) {
		if (ptr[i] == '=') {
			length++;
		}
	}

	for (int32_t i = 0x0; i < length; i++) {
		delimiter = strchr(ptr, '=');
		key = (uint8_t*)_malloc(sizeof(uint8_t) * (delimiter - ptr + 0x1));
		strncpy(key, ptr, delimiter - ptr);
		key[delimiter - ptr] = 0x0;

		ptr = delimiter + 0x1;
		if (i + 1 == length) {
			delimiter = strchr(delimiter, ' ');
		} else {
			delimiter = strchr(delimiter, '&');
		}
		value = (uint8_t*)_malloc(sizeof(uint8_t) * (delimiter - ptr + 0x1));
		strncpy(value, ptr, delimiter - ptr);
		value[delimiter - ptr] = 0x0;

		hash_table_push(result, key, value);
		ptr = delimiter + 0x1;
	}

	return result;
}
