#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

/**
 * error_exit - prints an error message and exits
 * @msg: the error message
 * @file: filename related to the error
 * @code: exit code
 */
void error_exit(const char *msg, const char *file, int code)
{
	dprintf(STDERR_FILENO, "Error: %s %s\n", msg, file);
	exit(code);
}

/**
 * check_close - closes a file descriptor and exits if it fails
 * @fd: the file descriptor
 */
void check_close(int fd)
{
	int c;

	c = close(fd);
	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: arguments (file_from file_to)
 *
 * Return: 0 on success, exits with error codes on failure
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to, n_read, n_written;
	char buffer[BUF_SIZE];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		error_exit("Can't read from file", argv[1], 98);

	n_read = read(fd_from, buffer, BUF_SIZE);
	if (n_read == -1)
	{
		check_close(fd_from);
		error_exit("Can't read from file", argv[1], 98);
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		check_close(fd_from);
		error_exit("Can't write to", argv[2], 99);
	}

	while (n_read > 0)
	{
		n_written = write(fd_to, buffer, n_read);
		if (n_written != n_read)
		{
			check_close(fd_from);
			check_close(fd_to);
			error_exit("Can't write to", argv[2], 99);
		}

		n_read = read(fd_from, buffer, BUF_SIZE);
		if (n_read == -1)
		{
			check_close(fd_from);
			check_close(fd_to);
			error_exit("Can't read from file", argv[1], 98);
		}
	}

	check_close(fd_from);
	check_close(fd_to);
	return (0);
}
