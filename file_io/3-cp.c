#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

/**
 * error_exit - print an error message and exit
 * @msg: message string
 * @file: file name or fd as string
 * @code: exit code
 */
void error_exit(const char *msg, const char *file, int code)
{
	dprintf(STDERR_FILENO, "Error: %s %s\n", msg, file);
	exit(code);
}

/**
 * safe_close - closes a file descriptor and checks for errors
 * @fd: file descriptor
 */
void safe_close(int fd)
{
	char fd_str[12];

	if (close(fd) == -1)
	{
		snprintf(fd_str, sizeof(fd_str), "%d", fd);
		error_exit("Can't close fd", fd_str, 100);
	}
}

/**
 * copy_file - copy content from one file descriptor to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source file name
 * @file_to: destination file name
 */
void copy_file(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t n_read, n_written, total_written;
	char buffer[BUF_SIZE];

	while (1)
	{
		n_read = read(fd_from, buffer, BUF_SIZE);
		if (n_read == -1)
			error_exit("Can't read from file", file_from, 98);
		if (n_read == 0)
			break;

		total_written = 0;
		while (total_written < n_read)
		{
			n_written = write(fd_to, buffer + total_written, n_read - total_written);
			if (n_written == -1)
				error_exit("Can't write to", file_to, 99);
			total_written += n_written;
		}
	}
}

/**
 * main - copy the content of a file to another file
 * @argc: number of arguments
 * @argv: argument vector
 *
 * Return: 0 on success, exits on error
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
