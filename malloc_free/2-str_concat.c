#include <stdlib.h>
#include "main.h"

/**
 * str_concat - concatenates two strings into a newly allocated space in memory
 * @s1: first string (can be NULL, treated as empty string)
 * @s2: second string (can be NULL, treated as empty string)
 *
 * Return: pointer to the newly allocated concatenated string,
 *         or NULL if memory allocation fails
 */

char *str_concat(char *s1, char *s2)
{
	unsigned int len1 = 0;
	unsigned int len2 = 0;
	unsigned int i, j;
	char *concat;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";

	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	concat = malloc((len1 + len2 + 1) * sizeof(char));

	if (concat == 0)
		return (NULL);

	for (i = 0; i < len1; i++)
		concat[i] = s1[i];

	for (j = 0; j < len2; j++)
		concat[len1 + j] = s2[j];

	concat[len1 + len2] = '\0';

	return (concat);
}
