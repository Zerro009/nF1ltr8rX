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

void middleware_print_response_status(const http_response *response) {
	if (has_colors() == FALSE) {
		printf("[%s]\n", response->status);
		return;

	}

	initscr();
	start_color();

	if (response->status[0] == '2') {
		init_pair(0x1, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(0x1));
		printw("[%s]\n", response->status);
		attroff(COLOR_PAIR(0x1));
	} else if ((response->status[0] == '4') || (response->status[0] == '5')) {
		init_pair(0x1, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(0x1));
		printw("[%s]\n", response->status);
		attroff(COLOR_PAIR(0x1));
	}

	endwin();
}
