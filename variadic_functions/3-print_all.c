#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_all - prints any type based on format
 * @format: string of type identifiers (c, i, f, s)
 */
void print_all(const char * const format, ...)
{
    va_list args;
    unsigned int j = 0;
    char *str;
    int printed = 0;

    va_start(args, format);

    while (format && format[j])
    {
        if (format[j] == 'c')
            printed += printf("%s%c", printed ? ", " : "", va_arg(args, int));
        if (format[j] == 'i')
            printed += printf("%s%d", printed ? ", " : "", va_arg(args, int));
        if (format[j] == 'f')
            printed += printf("%s%f", printed ? ", " : "", va_arg(args, double));
        if (format[j] == 's')
        {
            str = va_arg(args, char *);
            if (!str)
                str = "(nil)";
            printed += printf("%s%s", printed ? ", " : "", str);
        }
        j++;
    }

    va_end(args);
    printf("\n");
}
