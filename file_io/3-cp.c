#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * close_file - Closes a file descriptor and handles errors.
 * @fd: File descriptor to close.
 */
void close_file(int fd)
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
 * error_read - Handles read errors.
 * @file_from: Source file name.
 */
void error_read(char *file_from)
{
	dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
	exit(98);
}

/**
 * error_write - Handles write/create errors.
 * @file_to: Destination file name.
 */
void error_write(char *file_to)
{
	dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
	exit(99);
}

/**
 * main - Copies the content of a file to another file.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to, rd, wr;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buffer = malloc(1024);
	if (buffer == NULL)
		error_write(argv[2]);

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		error_read(argv[1]);

	fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		free(buffer);
		error_write(argv[2]);
	}

	while ((rd = read(fd_from, buffer, 1024)) > 0)
	{
		wr = write(fd_to, buffer, rd);
		if (wr != rd)
		{
			free(buffer);
			error_write(argv[2]);
		}
	}
	if (rd == -1)
	{
		free(buffer);
		error_read(argv[1]);
	}

	free(buffer);
	close_file(fd_from);
	close_file(fd_to);
	return (0);
}
