#include <stdlib.h>
#include "main.h"

/**
 * malloc_checked - allocates memory using malloc
 * @b: number of bytes to allocate
 *
 * Return: pointer to the allocated memory
 *         if malloc fails, the function exits with status 98
 */

void *malloc_checked(unsigned int b)
{
	int *memory;

	memory = malloc(b);

	if (!memory)
		exit(98);

	return (memory);
}
