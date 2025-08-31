#include "main.h"

/**
 * int _isdigit - checks for a digit 0-9
 * @c: the char to check
 *
 * Return: 1 if digit , 0 otherwise
 */
int _isdigit(int c)
{

	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
