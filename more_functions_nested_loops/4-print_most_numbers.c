#include "main.h"

/**
 * print_most_numbers - print the numbers from 0 to 9 except 2 and 4
 *
 * Return: nothing
 */
void print_most_numbers(void)
{
	int n;

	for (n = 0; n <= 9; n++)
	{
		if (n != 2 && n != 4)
			_putchar('0' + n);
	}

	_putchar('\n');
}
