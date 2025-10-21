#include "hash_tables.h"

/**
 * key_index - Gives the index of a key in a hash table.
 * @key: The key to get the index for.
 * @size: The size of the array of the hash table.
 *
 * Description: Uses the hash_djb2 function to compute
 * the hash value of the key, then applies modulo with
 * the size of the array to get a valid index for the table.
 *
 * Return: The index at which the key/value pair should
 * be stored in the hash table array.
*/
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int index;

	if (!key || size == 0)
		return (0);

	index = hash_djb2(key) % size;

	return (index);
}
