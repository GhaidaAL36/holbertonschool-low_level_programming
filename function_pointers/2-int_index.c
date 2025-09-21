#include "function_pointers.h"

/**
 * int_index - searches for an element using a cmp function
 * @array: array to search
 * @size: number of elements
 * @cmp: function pointer to compare elements
 *
 * Return: index of first match, -1 if none
 */
int int_index(int *array, int size, int (*cmp)(int))
{
	int i;

	if (size <= 0)
		return (-1);

	for (i = 0; i < size; i++)
	{
		if (cmp(array[i]))
			return (i);
	}

	return (-1);
}
