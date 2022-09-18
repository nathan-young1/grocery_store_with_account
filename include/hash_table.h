#ifndef DICTIONARY_HEADER
#define DICTIONARY_HEADER
#include <stdbool.h>

typedef struct entry
{
	char *key;
	struct entry *next;
	void *value;
} entry;

typedef struct hashtable
{
	entry **entry_array;
	int size;
} hashtable;

hashtable *intialize_hashtable(int innerArraySize);
void hashtable_print(hashtable *dictionary);
int hash(char *key, int hashtable_size);
void hashtable_insert(char *key, void *value, hashtable *dictionary);
bool hashtable_delete(char *key, hashtable *dictionary);
entry *hashtable_lookup(char *key, hashtable *dictionary);

#endif