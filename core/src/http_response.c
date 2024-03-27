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

int32_t http_response_calc_total_bytes(http_response *response) {
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

	result += http_response_calc_content_length(response);

	return result;
}

int32_t http_response_calc_content_length(http_response *response) {
	int32_t result = 0x0;

	hash_table_entry *iter = response->body->begin;
	result++; // Adding '{'
	for (; iter; iter = iter->next) {
		result += 4; // Adding '\r\n "'
		result += strlen(iter->key);
		result += 4; // Adding '": "'
		result += strlen(iter->value);
		if (iter->next) {
			result += 2; // Adding '",'
		} else {
			result += 3; // Adding '"\r\n'
		}
	}
	result++; // Adding '}'

	return result;
}

void http_response_add_content_length_header(http_response *response, int32_t length) {
	int32_t string_length = snprintf(NULL, 0x0, "%d", length) + 1;
	uint8_t *value = (uint8_t*) _malloc(sizeof(uint8_t) * string_length);
	snprintf(value, string_length, "%d", length);
	hash_table_push(
		response->headers,
		"Content-Length",
		value
	);
}

void *http_response_to_raw(http_response *response) {
	int32_t content_length = http_response_calc_content_length(response);
	http_response_add_content_length_header(response, content_length);

	int32_t bytes = http_response_calc_total_bytes(response);
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

	// Body section
	iter = response->body->begin;
	strcat(result, "{");
	for (; iter; iter = iter->next) {
		strcat(result, "\r\n \"");
		strcat(result, iter->key);
		strcat(result, "\": \"");
		strcat(result, iter->value);
		if (iter->next) {
			strcat(result, "\",");
		} else {
			strcat(result, "\"\r\n");
		}
	}
	strcat(result, "}");

	return result;
}
