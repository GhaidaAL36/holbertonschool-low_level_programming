#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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
 * safe_close - closes a file descriptor and exits if it fails
 * @fd: the file descriptor
 */
void safe_close(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - copies content from fd_from to fd_to
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source filename for error messages
 * @file_to: destination filename for error messages
 */
void copy_file(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t n_read, n_written;
	char buffer[BUF_SIZE];

	while ((n_read = read(fd_from, buffer, BUF_SIZE)) > 0)
	{
		n_written = write(fd_to, buffer, n_read);
		if (n_written != n_read)
			error_exit("Can't write to", file_to, 99);
	}
	if (n_read == -1)
		error_exit("Can't read from file", file_from, 98);
}

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: arguments (file_from file_to)
 *
 * Return: 0 on success, exits with proper code on failure
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		error_exit("Can't read from file", argv[1], 98);

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		safe_close(fd_from);
		error_exit("Can't write to", argv[2], 99);
	}

	copy_file(fd_from, fd_to, argv[1], argv[2]);

	safe_close(fd_from);
	safe_close(fd_to);

	return (0);
}
