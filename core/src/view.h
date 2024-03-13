#ifndef __VIEW_H__
#define __VIEW_H__

#include "http_request.h"

typedef struct {
	uint8_t method[METHOD_MAX_SIZE];
	void (*func)();
} view;

view *view_construct(const uint8_t *method, void (*func)());

#endif
