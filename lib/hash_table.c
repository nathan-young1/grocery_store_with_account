#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Todo : maybe add load function for hash table later.
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


hashtable *intialize_hashtable(int innerArraySize)
{
	hashtable *new_hashtable = malloc(sizeof(hashtable));

	new_hashtable->entry_array = (entry **)malloc(sizeof(entry *) * innerArraySize);
	new_hashtable->size = innerArraySize;

	// Set all pointers in the array to NULL.
	for (int i = 0; i < innerArraySize; i++)
		new_hashtable->entry_array[i] = NULL;

	return new_hashtable;
}

void hashtable_print(hashtable *table)
{
	for (int i = 0; i < table->size; i++)
	{
		entry *item = table->entry_array[i];
		if (item != NULL)
		{
			printf("\t%d:\t", i);
			// iterate throught the linked list (in case of collision) and print the content.
			while (item != NULL)
			{
				printf("%s --- ", item->key);
				item = item->next;
			}
			printf("\n");
		}
		else
		{
			printf("\t%d:\t ~~~~\n", i);
		}
	}
}

int hash(char *key, int hashtable_size)
{
	size_t keyLength = strnlen(key, sizeof(size_t));

	int ascii_code_sum = 0;

	for (int i = 0; i < keyLength; i++)
	{
		ascii_code_sum += key[i];
	}

	int hash_index = ascii_code_sum % hashtable_size;
	return hash_index;
}

void hashtable_insert(char *key, void *value, hashtable *table)
{
	// Set the new Entry to be the head node in it's index.
	int index = hash(key, table->size);

	// create a new entry on the heap.
	entry *newEntry = malloc(sizeof(entry));
	newEntry->key = key;
	newEntry->value = value;

	// Insert into the hashtable.
	newEntry->next = table->entry_array[index];
	table->entry_array[index] = newEntry;
}

// Returns a bool value on whether the delete was successful.
bool hashtable_delete(char *key, hashtable *table)
{
	int index = hash(key, table->size);
	entry *entry_from_hash_table = table->entry_array[index];
	entry *prev = NULL;

	// When the key does not exist on the hashtable.
	if (entry_from_hash_table == NULL)
		return false;
	else
	{
		// Will iterate through the linked list in case of collision.
		while (
			entry_from_hash_table != NULL &&
			strcmp(entry_from_hash_table->key, key) != 0)
		{
			prev = entry_from_hash_table;
			entry_from_hash_table = entry_from_hash_table->next;
		}

		// When the key does not exist on the hashtable.
		if (entry_from_hash_table == NULL)
			return false;

		// Key exist in the hashtable.
		if (prev == NULL)
		{
			// if the item to be deleted is the head of the linked list in a collision.
			table->entry_array[index] = entry_from_hash_table->next;
		}
		else
		{
			// Repoint nodes to the right entry.
			prev->next = entry_from_hash_table->next;
		}

		// clean up memory.
		free(entry_from_hash_table);
		return true;
	}
}

entry *hashtable_lookup(char *key, hashtable *table)
{
	int index = hash(key, table->size);
	entry *entry_from_hash_table = table->entry_array[index];

	// When the key does not exist on the hashtable.
	if (entry_from_hash_table == NULL)
		return NULL;
	else
	{
		// Will iterate through the linked list in case of collision.
		while (
			entry_from_hash_table != NULL &&
			strcmp(entry_from_hash_table->key, key) != 0)
		{
			entry_from_hash_table = entry_from_hash_table->next;
		}

		// When the key does not exist on the hashtable.
		if (entry_from_hash_table == NULL)
			return NULL;

		return entry_from_hash_table;
	}
}