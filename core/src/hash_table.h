#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdint.h>

#include "memory.h"

typedef struct hash_table_entry {
	struct hash_table_entry *next;
	uint8_t *key;
	void *value;
} hash_table_entry;

typedef struct {
	hash_table_entry *begin;
	int32_t len;
} hash_table;

hash_table *hash_table_construct();
int32_t hash_table_push(hash_table *table, uint8_t *key, void *value);
void *hash_table_at(hash_table *table, uint8_t *key);

#endif
