#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

/**
 * error_exit - prints an error message and exits
 * @msg: message to print
 * @file: file name
 * @code: exit code
 */
void error_exit(const char *msg, const char *file, int code)
{
	dprintf(STDERR_FILENO, "Error: %s %s\n", msg, file);
	exit(code);
}

/**
 * check_close - closes a file descriptor and exits on failure
 * @fd: file descriptor to close
 */
void check_close(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - copies content of one file to another
 * @file_from: source file
 * @file_to: destination file
 */
void copy_file(const char *file_from, const char *file_to)
{
	int fd_from, fd_to, n_read, n_written;
	char buffer[BUF_SIZE];

	fd_from = open(file_from, O_RDONLY);
	if (fd_from == -1)
		error_exit("Can't read from file", file_from, 98);

	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		close(fd_from);
		error_exit("Can't write to", file_to, 99);
	}

	while ((n_read = read(fd_from, buffer, BUF_SIZE)) > 0)
	{
		n_written = write(fd_to, buffer, n_read);
		if (n_written != n_read)
		{
			close(fd_from);
			close(fd_to);
			error_exit("Can't write to", file_to, 99);
		}
	}

	if (n_read == -1)
	{
		close(fd_from);
		close(fd_to);
		error_exit("Can't read from file", file_from, 98);
	}

	check_close(fd_from);
	check_close(fd_to);
}

/**
 * main - entry point, checks args and calls copy_file
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	copy_file(av[1], av[2]);
	return (0);
}
