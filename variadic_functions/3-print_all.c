#include "variadic_functions.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * print_all - prints anything
 * @format: list of types of arguments
 *
 * Description: c: char, i: integer, f: float, s: string
 * If a string is NULL, prints (nil)
 * Any other character is ignored
 */
void print_all(const char * const format, ...)
{
	va_list args;
	unsigned int i = 0;
	char *str, *sep = "";

	va_start(args, format);

	while (format && format[i])
	{
		if (format[i] == 'c')
		{
			printf("%s%c", sep, va_arg(args, int));
		}
		if (format[i] == 'i')
		{
			printf("%s%d", sep, va_arg(args, int));
		}
		if (format[i] == 'f')
		{
			printf("%s%f", sep, va_arg(args, double));
		}
		if (format[i] == 's')
		{
			str = va_arg(args, char *);
			if (!str)
				str = "(nil)";
			printf("%s%s", sep, str);
		}
		if (format[i] == 'c' || format[i] == 'i' ||
		    format[i] == 'f' || format[i] == 's')
			sep = ", ";
		i++;
	}
	printf("\n");
	va_end(args);
}

