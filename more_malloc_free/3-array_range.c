#include <stdlib.h>
#include "main.h"

/**
 * array_range - creates an array of integers from min to max
 * @min: starting value of the array
 * @max: ending value of the array
 *
 * Return: pointer to newly allocated array, or NULL on failure
 */
int *array_range(int min, int max)
{
	int *array;
	int i, size;

	if (min > max)
		return (NULL);

	size = max - min + 1;
	array = malloc(size * sizeof(int));
	if (!array)
		return (NULL);

	for (i = 0; i < size; i++)
		array[i] = min + i;

	return (array);
}
