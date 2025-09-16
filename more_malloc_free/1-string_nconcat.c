#include <stdlib.h>
#include <string.h>
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

	len1 = (s1 != NULL) ? strlen(s1) : 0;
	len2 = (s2 != NULL) ? strlen(s2) : 0;


	if (n > len2)
		copy_len = len2;
	else
		copy_len = n;

	concat = malloc((len1 + copy_len + 1) * sizeof(char));

	if (!concat)
		return (NULL);

	if (s1)
	for (i = 0; i < len1; i++)
	{
		concat[i] = s1[i];
	}
	if (s2)
	for (j = 0; j < copy_len; j++)
	{
		concat[len1 + j] = s2[j];
	}

	concat[len1 + copy_len] = '\0';

	return (concat);

}
