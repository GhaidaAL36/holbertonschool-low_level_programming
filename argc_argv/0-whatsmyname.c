#include <stdio.h>

/**
 * main - prints its own program name
 * @argc: number of arguments (unused)
 * @argv: array of arguments, argv[0] is program name
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	(void)argc; /* unused variable */
	printf("%s\n", argv[0]);
	return (0);
}
