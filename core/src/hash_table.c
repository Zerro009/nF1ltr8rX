#include "hash_table.h"

hash_table *hash_table_construct() {
	hash_table *result = (hash_table*) _malloc(sizeof(hash_table));
	result->len = 0x0;
	result->begin = NULL;

	return result;
}

int32_t hash_table_push(hash_table *table, uint8_t *key, void *value) {
	hash_table_entry *entry = (hash_table_entry*) _malloc(sizeof(hash_table_entry));
	entry->key = key;
	entry->value = value;
	entry->next = table->begin;
	table->begin = entry;
	table->len++;

	return 0x1;
}

void *hash_table_at(hash_table *table, uint8_t *key) {
	if (!table->begin) {
		return NULL;
	}

	hash_table_entry *iter = table->begin;
	for (; iter ; iter = iter->next) {
		if (!strcmp(iter->key, key)) {
			return iter->value;
		}
		if (!iter->next) {
			return NULL;
		}
	}

	return NULL;
}
