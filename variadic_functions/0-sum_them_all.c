#include "variadic_functions.h"
#include <stdarg.h>

/**
 * sum_them_all - returns the sum of all its parameters
 * @n: the number of integers passed to the function
 *
 * Return: the sum of all parameters, or 0 if n is 0
 */
int sum_them_all(const unsigned int n, ...)
{
	unsigned int i;
	unsigned int num;
	unsigned int sum = 0;
	va_list args;

	if (n == 0)
		return (0);

	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		num = va_arg(args, unsigned int);
		sum += num;
	}

	return (sum);
}
