#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *_malloc(uint32_t size);
void _free(void *ptr);

#endif
