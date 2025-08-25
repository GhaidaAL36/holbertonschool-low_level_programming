#include <stdio.h>
#include "main.h"

/**
 * _abs - computes absolute value of an integer
 * @n: the number to check
 *
 * Return: absolute value of n
 */
int _abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}
