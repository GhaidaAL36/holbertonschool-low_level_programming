#include <stdlib.h>
#include "main.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 *           containing a copy of the string given as a parameter
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string, or NULL if str is NULL
 *         or if memory allocation fails
 */

char *_strdup(char *str)
{
	unsigned int len = 0;
	unsigned int i;
	char *copy;

	if (str == 0)
		return (NULL);

	while (str[len] != '\0')
		len++;

	copy = malloc((len + 1) * sizeof(char));
	if (copy == 0)
		return (0);

	for (i = 0; i < len; i++)
	{
		copy[i] = str[i];
	}

	copy[len] = '\0';

	return (copy);
}
