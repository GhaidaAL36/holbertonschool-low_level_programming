#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_all - prints any type of argument based on format string
 * @format: string of types (c: char, i: int, f: float, s: string)
 *
 * Description: prints each argument separated by ", ".
 * If a string is NULL, prints (nil). Prints a newline at the end.
 * No else/else if is used. Maximum 2 if statements and < 9 variables.
 */
void print_all(const char * const format, ...)
{
    va_list args;
    unsigned int i = 0;
    char *str;
    char *sep = "";

    if (!format)
        return;

    va_start(args, format);

    while (format[i])
    {
        if (format[i] == 'c')
            printf("%s%c", sep, va_arg(args, int));

        if (format[i] == 'i')
            printf("%s%d", sep, va_arg(args, int));

        if (format[i] == 'f')
            printf("%s%f", sep, va_arg(args, double));

        if (format[i] == 's')
        {
            str = va_arg(args, char *);
            printf("%s%s", sep, str ? str : "(nil)");
        }

        sep = ", ";
        i++;
    }

    va_end(args);
    printf("\n");
}
