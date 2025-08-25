#include <stdio.h>
#include "main.h"

/**
 * print_last_digit - print last digit of a number
 * @n: The number to check.
 *
 * Return: value of last digi
 */
int print_last_digit(int n)
{
	int last_digit;

	last_digit = n % 10;

	if (last_digit < 0)
		last_digit = -last_digit;

	_putchar('0' + last_digit);

	return (last_digit);
}
