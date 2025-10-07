#include "lists.h"
#include <stdlib.h>

/**
 * free_list - Frees a list_t list
 * @head: Pointer to the head of the list
 *
 * Description: Frees each node and its string
 */
void free_list(list_t *head)
{
	list_t *temp;

	while (head != NULL)
	{
		temp = head->next; /* Store pointer to next node */
		free(head->str);   /* Free the string */
		free(head);        /* Free the node */
		head = temp;       /* Move to next node */
	}
}
