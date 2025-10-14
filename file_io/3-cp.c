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
 * error_exit - Prints error and exits with code.
 * @code: Exit code.
 * @msg: Message format.
 * @arg: Argument for message.
 */
void error_exit(int code, const char *msg, char *arg)
{
	dprintf(STDERR_FILENO, msg, arg);
	exit(code);
}

/**
 * main - Copies content of one file to another.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to, rd, wr;
	char buffer[1024];

	if (argc != 3)
		error_exit(97, "Usage: cp file_from file_to\n", "");

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		error_exit(98, "Error: Can't read from file %s\n", argv[1]);

	fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd_to == -1)
		error_exit(99, "Error: Can't write to %s\n", argv[2]);

	while ((rd = read(fd_from, buffer, 1024)) != 0)
	{
		if (rd == -1)
			error_exit(98, "Error: Can't read from file %s\n", argv[1]);

		wr = write(fd_to, buffer, rd);
		if (wr == -1 || wr != rd)
			error_exit(99, "Error: Can't write to %s\n", argv[2]);
	}

	close_file(fd_from);
	close_file(fd_to);
	return (0);
}
