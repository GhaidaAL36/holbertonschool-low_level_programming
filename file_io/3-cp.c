#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

/**
 * close_file - Closes a file descriptor or exits with code 100.
 * @fd: File descriptor to close.
 */
void close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * exit_error - Prints an error message and exits with the given code.
 * @code: Exit code (97, 98, 99, or 100)
 * @msg: Error message (Usage, Can't read/write/close)
 * @file: Related filename (can be NULL)
 */
void exit_error(int code, const char *msg, const char *file)
{
	if (file)
		dprintf(STDERR_FILENO, "%s %s\n", msg, file);
	else
		dprintf(STDERR_FILENO, "%s\n", msg);
	exit(code);
}

/**
 * open_dest - Opens destination file with correct perms.
 * Ensures 0664 perms only if newly created.
 * @path: Destination filename
 * Return: File descriptor.
 */
int open_dest(const char *path)
{
	int fd;

	fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0664);
	if (fd != -1)
	{
		if (fchmod(fd, 0664) == -1)
		{
			close(fd);
			exit_error(99, "Error: Can't write to", path);
		}
		return (fd);
	}

	if (errno == EEXIST)
	{
		fd = open(path, O_WRONLY | O_TRUNC);
		if (fd == -1)
			exit_error(99, "Error: Can't write to", path);
		return (fd);
	}
	exit_error(99, "Error: Can't write to", path);
	return (-1);
}

/**
 * copy_contents - Copies data from src_fd to dst_fd.
 * @src_fd: Source file descriptor.
 * @dst_fd: Destination file descriptor.
 * @src_name: Source filename.
 * @dst_name: Destination filename.
 */
void copy_contents(int src_fd, int dst_fd, const char *src_name,
		   const char *dst_name)
{
	ssize_t r, w;
	char buf[BUF_SIZE];

	while ((r = read(src_fd, buf, BUF_SIZE)) > 0)
	{
		w = write(dst_fd, buf, r);
		if (w == -1 || w != r)
			exit_error(99, "Error: Can't write to", dst_name);
	}
	if (r == -1)
		exit_error(98, "Error: Can't read from file", src_name);
}

/**
 * main - Copies the content of one file into another.
 * @argc: Argument count.
 * @argv: Argument values.
 * Return: 0 on success, exits on error.
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to;

	if (argc != 3)
		exit_error(97, "Usage: cp file_from file_to", NULL);

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
		exit_error(98, "Error: Can't read from file", argv[1]);

	fd_to = open_dest(argv[2]);
	copy_contents(fd_from, fd_to, argv[1], argv[2]);

	close_file(fd_from);
	close_file(fd_to);

	return (0);
}

