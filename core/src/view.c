#include "view.h"

view *view_construct(const uint8_t *method, void (*func)()) {
	view *result = (view *) _malloc(sizeof(view));
	strncpy(result->method, method, METHOD_MAX_SIZE);
	result->func = func;

	return result;
}
