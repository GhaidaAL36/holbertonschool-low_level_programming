#include "function_pointers.h"

/**
 * print_name - executes a function on a name
 * @name: string to print
 * @f: pointer to a function that takes a string
 *
 * Return: void
 */
void print_name(char *name, void (*f)(char *))
{
	f(name);
}
