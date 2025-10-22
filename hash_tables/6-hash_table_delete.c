#include "hash_tables.h"
#include <stdlib.h>

/**
	* hash_table_delete - Deletes a hash table
	* @ht: The hash table to delete
	*
	* Description: Frees all nodes, keys, and values,
	* then frees the array and the hash table itself.
	*/
void hash_table_delete(hash_table_t *ht)
{
	hash_node_t *node, *temp;
	unsigned long int i;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		node = ht->array[i];
		while (node != NULL)
		{
			temp = node->next;
			free(node->key);
			free(node->value);
			free(node);
			node = temp;
		}
	}

	free(ht->array);
	free(ht);
}
