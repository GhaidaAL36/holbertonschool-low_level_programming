#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUF 1024

/**
 * close_or_die - close fd or exit 100
 * @fd: file descriptor
 */
static void close_or_die(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * open_source - open source file for reading
 * @file: filename
 * Return: file descriptor
 */
static int open_source(const char *file)
{
	int fd = open(file, O_RDONLY);

	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file);
		exit(98);
	}
	return (fd);
}

/**
 * open_dest - open/create destination file for writing
 * @file: filename
 * Return: file descriptor
 */
static int open_dest(const char *file)
{
	int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file);
		exit(99);
	}
	return (fd);
}

/**
 * copy_content - copy from src_fd to dest_fd
 * @src_fd: source file descriptor
 * @dest_fd: destination file descriptor
 * @src_file: source filename (for error messages)
 * @dest_file: destination filename (for error messages)
 */
static void copy_content(int src_fd, int dest_fd, const char *src_file,
			const char *dest_file)
{
	ssize_t r, w;
	char buf[BUF];

	while ((r = read(src_fd, buf, BUF)) > 0)
	{
		ssize_t off = 0;

		while (off < r)
		{
			w = write(dest_fd, buf + off, r - off);
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", dest_file);
				close_or_die(src_fd);
				close_or_die(dest_fd);
				exit(99);
			}
			off += w;
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", src_file);
		close_or_die(src_fd);
		close_or_die(dest_fd);
		exit(98);
	}
}

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int f_from, f_to;

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	f_from = open_source(av[1]);
	f_to = open_dest(av[2]);
	copy_content(f_from, f_to, av[1], av[2]);
	close_or_die(f_from);
	close_or_die(f_to);

	return (0);
}
