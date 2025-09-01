#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @s: string to change
 *
 * Return: pointer to the changed string
 */
char *cap_string(char *s)
{
	int i = 0;

	if (s[i] >= 'a' && s[i] <= 'z')
		s[i] = s[i] - 'a' + 'A';
	i++;
	while (s[i])
	{
		if ((s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n' ||
		     s[i - 1] == ',' || s[i - 1] == ';' || s[i - 1] == '.' ||
		     s[i - 1] == '!' || s[i - 1] == '?' || s[i - 1] == '"' ||
		     s[i - 1] == '(' || s[i - 1] == ')' || s[i - 1] == '{' ||
		     s[i - 1] == '}') && (s[i] >= 'a' && s[i] <= 'z'))
			s[i] = s[i] - 'a' + 'A';
		i++;
	}
	return (s);
}
