#include "middleware.h"

void middleware_handle_request(const http_request *request) {
	middleware_print_request_data(request);
}

void middleware_print_request_data(const http_request *request) {
	// Print time of receiving request
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("[%d-%d-%d] ", tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	printf("%s %s ", request->method, request->uri);
}
