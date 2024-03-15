#ifndef __VIEW_H__
#define __VIEW_H__

#include "http_request.h"
#include "http_response.h"

typedef struct {
	uint8_t method[METHOD_MAX_SIZE];
	http_response *(*func)(http_request*);
} view;

view *view_construct(const uint8_t *method, http_response *(*func)(http_request*));

#endif
