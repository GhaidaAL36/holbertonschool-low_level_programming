#include <stdlib.h>
#include "main.h"

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @str: string to copy
 *
 * Return pointer to the duplicated string, NULL otherwise
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

	for (i = 0; i < len; i++)
	{
		copy[i] = str[i];
	}

	copy[len] = '\0';

	return (copy);
}
