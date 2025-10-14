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
 * main - copy content of a file to another file
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int f_from, f_to;
	ssize_t r, w;
	char buf[BUF];

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	/* open source file */
	f_from = open(av[1], O_RDONLY);
	if (f_from == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		exit(98);
	}

	/* open/create destination file with truncate */
	f_to = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (f_to == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
		close_or_die(f_from);
		exit(99);
	}

	/* read from source and write to destination in 1024 bytes */
	while ((r = read(f_from, buf, BUF)) > 0)
	{
		ssize_t offset = 0;

		/* handle short writes */
		while (offset < r)
		{
			w = write(f_to, buf + offset, r - offset);
			if (w == -1)
			{
				dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]);
				close_or_die(f_from);
				close_or_die(f_to);
				exit(99);
			}
			offset += w;
		}
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]);
		close_or_die(f_from);
		close_or_die(f_to);
		exit(98);
	}

	close_or_die(f_from);
	close_or_die(f_to);

	return (0);
}
