#include "view.h"

view *view_construct(const uint8_t *method, http_response *(*func)(http_request*)) {
	view *result = (view *) _malloc(sizeof(view));
	strncpy(result->method, method, METHOD_MAX_SIZE);
	result->func = func;

	return result;
}
