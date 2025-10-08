#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

/**
 * print_error_and_exit - prints error message and exits with code
 * @msg: message string
 * @file: file name
 * @code: exit code
 */
void print_error_and_exit(const char *msg, const char *file, int code)
{
	dprintf(STDERR_FILENO, "Error: %s %s\n", msg, file);
	exit(code);
}

/**
 * copy_content - copies content from fd_from to fd_to
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source file name (for error messages)
 * @file_to: destination file name (for error messages)
 */
void copy_content(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t n_read, n_written;
	char buffer[BUF_SIZE];

	while ((n_read = read(fd_from, buffer, BUF_SIZE)) > 0)
	{
		n_written = write(fd_to, buffer, n_read);
		if (n_written != n_read)
			print_error_and_exit("Can't write to", file_to, 99);
	}
	if (n_read == -1)
		print_error_and_exit("Can't read from file", file_from, 98);
}

/**
 * close_fd - closes a file descriptor and handles errors
 * @fd: file descriptor to close
 * @file: file name (for error messages)
 */
void close_fd(int fd, char *file)
{
	if (close(fd) == -1)
		print_error_and_exit("Can't close fd", file, 100);
}

/**
 * main - copies content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
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
		print_error_and_exit("Can't read from file", argv[1], 98);

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		close_fd(fd_from, argv[1]);
		print_error_and_exit("Can't write to", argv[2], 99);
	}

	copy_content(fd_from, fd_to, argv[1], argv[2]);
	close_fd(fd_from, argv[1]);
	close_fd(fd_to, argv[2]);

	return (0);
}
