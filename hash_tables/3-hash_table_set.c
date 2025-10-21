#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>

/**
	* create_node - Creates a new hash node with key and value.
	* @key: The key for the node.
	* @value: The value for the node.
	*
	* Return: Pointer to the new node, or NULL on failure.
	*/
hash_node_t *create_node(const char *key, const char *value)
{
	hash_node_t *node = malloc(sizeof(hash_node_t));

	if (!node)
	return (NULL);

	node->key = strdup(key);
	if (!node->key)
	{
	free(node);
	return (NULL);
	}

	node->value = strdup(value);
	if (!node->value)
	{
	free(node->key);
	free(node);
	return (NULL);
	}

	node->next = NULL;
	return (node);
}

/**
	* update_value - Updates the value of an existing node.
	* @node: The node to update.
	* @value: The new value.
	*
	* Return: 1 if successful, 0 otherwise.
	*/
int update_value(hash_node_t *node, const char *value)
{
	char *new_value = strdup(value);

	if (!new_value)
	return (0);

	free(node->value);
	node->value = new_value;
	return (1);
}

/**
	* hash_table_set - Adds or updates an element in the hash table.
	* @ht: The hash table.
	* @key: The key.
	* @value: The value.
	*
	* Return: 1 if succeeded, 0 otherwise.
	*/
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	hash_node_t *current, *new_node;

	if (!ht || !key || *key == '\0' || !value)
	return (0);

	index = key_index((const unsigned char *)key, ht->size);
	current = ht->array[index];

	while (current)
	{
	if (strcmp(current->key, key) == 0)
	return (update_value(current, value));
	current = current->next;
	}

	new_node = create_node(key, value);
	if (!new_node)
	return (0);

	new_node->next = ht->array[index];
	ht->array[index] = new_node;

	return (1);
}
