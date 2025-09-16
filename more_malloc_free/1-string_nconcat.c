#include <stdlib.h>
#include "main.h"

/**
 * string_nconcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to copy from s2
 *
 * Return: pointer to newly allocated memory containing s1 followed
 *         by the first n bytes of s2, NULL on failure
 */

char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	unsigned int len1 = 0;
	unsigned int len2 = 0;
	unsigned int i, j;
	unsigned int copy_len = 0;
	char *concat;

	while (s1[len1] != '\0')
		len1++;

	while (s2[len2] != '\0')
		len2++;

	if (n > len2)
		copy_len = len2;
	else
		copy_len = n;

	concat = malloc((len1 + copy_len + 1) * sizeof(char));

	if (!concat)
		return (NULL);

	for (i = 0; i < len1; i++)
	{
		concat[i] = s1[i];
	}
	for (j = 0; j < copy_len; j++)
	{
		concat[len1 + j] = s2[j];
	}

	concat[len1 + copy_len] = '\0';

	return (concat);

}
