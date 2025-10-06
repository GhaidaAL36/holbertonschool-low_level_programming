#include "lists.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_list - prints all elements of a list_t list
 * @h: pointer to the first node of the list
 *
 * Return: the number of nodes
 * Format: [len] string (if str is NULL, print [0] (nil))
 */
size_t print_list(const list_t *h)
{
	size_t nodes = 0;

	while (h != 0)
	{
		if (h->str != 0)
			printf("[%u] %s\n", h->len, h->str);
		else
			printf("[0] (nil)\n");

		nodes++;
		h = h->next;
	}
	return (nodes);
}
