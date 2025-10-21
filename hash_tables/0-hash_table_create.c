#include "hash_tables.h"
#include <stdlib.h>

/**
	* hash_table_create - Creates a hash table.
	* @size: The size of the array.
	*
	* Description: Allocates memory for a new hash table of
	* size @size, initializes all array elements to NULL.
	* Returns NULL if memory allocation fails.
	*
	* Return: Pointer to the newly created hash table,
	* or NULL if something went wrong.
	*/
hash_table_t *hash_table_create(unsigned long int size)
{
	unsigned long int i;
	hash_table_t *ht = malloc(sizeof(hash_table_t));

	if (!ht)
		return (NULL);

	ht->size = size;

	ht->array = malloc(sizeof(hash_node_t *) * size);
	if (!ht->array)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	return (ht);
}
