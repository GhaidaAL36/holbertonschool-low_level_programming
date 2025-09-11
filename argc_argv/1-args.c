#include <stdio.h>

/**
 * main - prints the number of arguments passed into it
 * @argc: number of arguments (includes program name)
 * @argv: array of arguments (unused)
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	(void)argv; /* unused variable */
	printf("%d\n", argc - 1);
	return (0);
}
