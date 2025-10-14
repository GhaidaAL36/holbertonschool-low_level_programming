#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#define BUF_SIZE 1024

/**
 * exit_error - Prints an error message and exits with code.
 * @code: Exit code (97, 98, 99, 100)
 * @msg: Error message
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
 * close_file - Closes file descriptor or exits with code 100.
 * @fd: File descriptor
 */
void close_file(int fd)
{
	if (close(fd) == -1)
		exit_error(100, "Error: Can't close fd", NULL);
}

/**
 * open_dest - Opens destination file with 0664 perms.
 * @path: Destination filename
 * Return: File descriptor
 */
int open_dest(const char *path)
{
	int fd;

	fd = open(path, O_CREAT | O_EXCL | O_WRONLY, 0664);
	if (fd != -1)
		return (fd);

	if (errno == EEXIST)
	{
		fd = open(path, O_WRONLY | O_TRUNC, 0664);
		if (fd == -1)
			exit_error(99, "Error: Can't write to", path);
		if (fchmod(fd, 0664) == -1)
		{
			close(fd);
			exit_error(99, "Error: Can't write to", path);
		}
		return (fd);
	}

	exit_error(99, "Error: Can't write to", path);
	return (-1);
}

/**
 * copy_contents - Copies data from src_fd to dst_fd safely.
 * @src_fd: Source file descriptor
 * @dst_fd: Destination file descriptor
 * @src_name: Source filename
 * @dst_name: Destination filename
 */
void copy_contents(int src_fd, int dst_fd, const char *src_name,
		   const char *dst_name)
{
	ssize_t r, w;
	ssize_t total;
	char buf[BUF_SIZE];

	while (1)
	{
		r = read(src_fd, buf, BUF_SIZE);
		if (r == -1)
		{
			if (errno == EINTR)
				continue;
			exit_error(98, "Error: Can't read from file", src_name);
		}
		if (r == 0)
			break;

		total = 0;
		while (total < r)
		{
			w = write(dst_fd, buf + total, r - total);
			if (w == -1)
			{
				if (errno == EINTR)
					continue;
				exit_error(99, "Error: Can't write to", dst_name);
			}
			total += w;
		}
	}
}

/**
 * main - Copies the content of one file to another
 * @argc: Argument count
 * @argv: Argument values
 * Return: 0 on success
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
