#include "hash_tables.h"
#include <string.h>

/**
	* hash_table_get - Retrieves a value associated with a key.
	* @ht: The hash table to look into.
	* @key: The key you are looking for.
	*
	* Description: Uses key_index to find the correct index
	* in the hash table array, then traverses the linked list
	* at that index to find the matching key.
	*
	* Return: The value associated with the key, or NULL if not found.
	*/
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int index;
	hash_node_t *current;

	if (!ht || !key || *key == '\0')
	return (NULL);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];

	while (current)
	{
	if (strcmp(current->key, key) == 0)
	return (current->value);
	current = current->next;
	}

	return (NULL);
}
