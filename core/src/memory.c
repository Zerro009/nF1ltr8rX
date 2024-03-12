#include "memory.h"

void *_malloc(uint32_t size) {
	void *ptr = malloc(size);
	if (!ptr) {
		perror("ERROR::_malloc()");
		exit(1);
	}
	return ptr;
}
