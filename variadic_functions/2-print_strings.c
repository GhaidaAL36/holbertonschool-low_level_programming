#include "variadic_functions.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * print_strings - prints strings followed by a new line
 * @separator: string printed between each string
 * @n: number of strings passed to the function
 *
 * Description: If a string is NULL, prints (nil) instead.
 * If separator is NULL, it is ignored.
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
	unsigned int i;
	char *string;
	va_list args;

	if (n == 0)
	{
		printf("\n");
		return;
	}

	va_start(args, n);

	for (i = 0; i < n; i++)
	{
		string = va_arg(args, char*);

		if (string == NULL)
			printf("(nil)");
		else
			printf("%s", string);
		if (separator != NULL && i < n - 1)
			printf("%s", separator);
	}
	printf("\n");
}
