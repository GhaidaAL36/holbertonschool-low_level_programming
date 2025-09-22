#include "variadic_functions.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * print_all - prints any type of argument based on format string
 * @format: string of types (c: char, i: int, f: float, s: string)
 *
 * Description: Prints each argument separated by ", ".
 *              If a string is NULL, prints (nil).
 *              Prints a new line at the end.
 */
void print_all(const char * const format, ...)
{
	va_list args;
	unsigned int i = 0;
	char *str;
	char *separator = "";

	va_start(args, format);

	while (format && format[i])
	{
		if (format[i] == 'c')
			printf("%s%c", separator, va_arg(args, int));
		if (format[i] == 'i')
			printf("%s%d", separator, va_arg(args, int));
		if (format[i] == 'f')
			printf("%s%f", separator, va_arg(args, double));
		if (format[i] == 's')
		{
			str = va_arg(args, char *);
			if (!str)
				str = "(nil)";
			printf("%s%s", separator, str);
		}
		separator = ", ";
		i++;
	}

	va_end(args);
	printf("\n");
}
