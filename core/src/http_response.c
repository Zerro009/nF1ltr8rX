#include "http_response.h"

http_response *http_response_construct(const uint8_t *status, hash_table *headers, hash_table *body) {
	http_response *result = (http_response *) _malloc(sizeof(http_response));
	strcpy(result->version, "HTTP/1.1");
	strncpy(result->status, status, 4);
	if (!headers) {
		result->headers = hash_table_construct();
	} else {
		result->headers = headers;
	}
	if (!body) {
		result->body = hash_table_construct();
	} else {
		result->body = body;
	}

	return result;
}

int32_t http_response_calc_bytes(http_response *response) {
	int32_t result = 0x0;
	result += strlen(response->version); // Adding size of response version, ex. HTTP/1.1
	result += 0x1; // Adding ' '
	result += strlen(response->status); // Adding size of response status, ex. 404
	result += 0x2; // Adding '\r\n'

	hash_table_entry *iter = response->headers->begin;
	for (; iter ; iter = iter->next) {
		result += strlen(iter->key); // Adding header key's length
		result += 0x2; // Adding ': '
		result += strlen(iter->value); // Adding header value's length
		result += 0x2; // Adding '\r\n'
	}
	result += 0x2; // Adding '\r\n' as border between headers and body section
	return result;
}

void *http_response_to_raw(http_response *response) {
	int32_t bytes = http_response_calc_bytes(response);
	uint8_t *result = (uint8_t*) _malloc(sizeof(uint8_t) * bytes);

	// Starting line
	strcat(result, response->version);
	strcat(result, " ");
	strcat(result, response->status);
	strcat(result, "\r\n");

	// Headers section
	hash_table_entry *iter = response->headers->begin;
	for (; iter; iter = iter->next) {
		strcat(result, iter->key);
		strcat(result, ": ");
		strcat(result, iter->value);
		strcat(result, "\r\n");
	}
	strcat(result, "\r\n");

	printf("%s\n", result);
	return result;
}
