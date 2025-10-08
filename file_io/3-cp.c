#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * print_error_exit - prints an error message and exits with code
 * @code: exit code
 * @msg: message to print
 * @file: file name or fd string
 */
void print_error_exit(int code, char *msg, char *file)
{
	if (code == 100)
		dprintf(STDERR_FILENO, "Error: Can't close fd %s\n", file);
	else
		dprintf(STDERR_FILENO, "%s %s\n", msg, file);
	exit(code);
}

/**
 * open_fd - opens a file for reading or writing
 * @filename: file name
 * @flags: open flags
 * @perm: permissions for writing (ignored if reading)
 *
 * Return: file descriptor
 */
int open_fd(char *filename, int flags, mode_t perm)
{
	int fd = open(filename, flags, perm);

	if (fd == -1)
	{
		if (flags & O_RDONLY)
			print_error_exit(98, "Error: Can't read from file", filename);
		else
			print_error_exit(99, "Error: Can't write to", filename);
	}
	return (fd);
}

/**
 * copy_content - copies content from fd_from to fd_to
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source filename (for error messages)
 * @file_to: destination filename (for error messages)
 */
void copy_content(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t rd, wr;
	char buffer[1024];

	while (1)
	{
		rd = read(fd_from, buffer, sizeof(buffer));
		if (rd == -1)
			print_error_exit(98, "Error: Can't read from file", file_from);
		if (rd == 0)
			break; /* EOF */

		wr = write(fd_to, buffer, rd);
		if (wr == -1 || wr != rd)
			print_error_exit(99, "Error: Can't write to", file_to);
	}
}

/**
 * close_fd - closes a file descriptor
 * @fd: file descriptor
 */
void close_fd(int fd)
{
	char fd_str[12];

	if (close(fd) == -1)
	{
		sprintf(fd_str, "%d", fd);
		print_error_exit(100, NULL, fd_str);
	}
}

/**
 * main - copies the content of a file to another file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, exits with specific codes on failure
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	umask(0);

	fd_from = open_fd(argv[1], O_RDONLY, 0);
	fd_to = open_fd(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fchmod(fd_to, 0664) == -1)
		print_error_exit(99, "Error: Can't write to", argv[2]);

	copy_content(fd_from, fd_to, argv[1], argv[2]);

	close_fd(fd_from);
	close_fd(fd_to);

	return (0);
}
