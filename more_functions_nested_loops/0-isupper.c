#include "main.h"

/**
 * _isupper - checks for uppercase character
 * @c: the character to check (passed as int)
 *
 * Return: 1 if c is uppercase, 0 otherwise
 */
int _isupper(int c)
{
	unsigned char uc = (unsigned char) c;

	if (uc >= 'A' && uc <= 'Z')
		return (1);
	return (0);
}
