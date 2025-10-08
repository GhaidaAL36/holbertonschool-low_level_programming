#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * print_error_exit - prints an error message and exits
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
 * copy_content - copies data from one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source filename (for error messages)
 * @file_to: destination filename (for error messages)
 */
void copy_content(int fd_from, int fd_to, char *file_from, char *file_to)
{
	ssize_t rd, wr;
	char buffer[1024];

	while ((rd = read(fd_from, buffer, 1024)) > 0)
	{
		wr = write(fd_to, buffer, rd);
		if (wr != rd)
			print_error_exit(99, "Error: Can't write to", file_to);
	}

	if (rd == -1)
		print_error_exit(98, "Error: Can't read from file", file_from);
}

/**
 * close_fd - closes a file descriptor
 * @fd: file descriptor to close
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
 * open_fd - opens a file, either for reading or writing
 * @filename: name of the file
 * @flags: flags for open()
 * @perm: permission bits (ignored if reading)
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
 * main - entry point to copy file_from to file_to
 * @argc: number of arguments
 * @argv: arguments
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

	fd_from = open_fd(argv[1], O_RDONLY, 0);
	fd_to = open_fd(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);

	copy_content(fd_from, fd_to, argv[1], argv[2]);

	close_fd(fd_from);
	close_fd(fd_to);

	return (0);
}
