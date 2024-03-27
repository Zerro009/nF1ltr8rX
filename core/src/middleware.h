#ifndef __MIDDLEWARE_H__
#define __MIDDLEWARE_H__

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "http_request.h"
#include "http_response.h"

void middleware_handle_request(const http_request *request);

// Middleware handlers
void middleware_print_request_data(const http_request *request);

#endif
