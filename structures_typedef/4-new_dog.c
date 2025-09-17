#include <stdlib.h>
#include "dog.h"

/**
 * new_dog - Creates a new dog
 * @name: Name of the dog
 * @age: Age of the dog
 * @owner: Owner of the dog
 *
 * Return: Pointer to the newly created dog (dog_t *)
 *         or NULL if malloc fails
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	int i, len;
	dog_t *d;

	if (name == NULL || owner == NULL)
		return (NULL);

	d = malloc(sizeof(dog_t));
	if (d == NULL)
		return (NULL);

	len = 0;
	while (name[len])
		len++;
	d->name = malloc(len + 1);
	if (d->name == NULL)
	{
		free(d);
		return (NULL);
	}
	for (i = 0; i < len; i++)
		d->name[i] = name[i];
	d->name[i] = '\0';

	len = 0;
	while (owner[len])
		len++;
	d->owner = malloc(len + 1);
	if (d->owner == NULL)
	{
		free(d->name);
		free(d);
		return (NULL);
	}
	for (i = 0; i < len; i++)
		d->owner[i] = owner[i];
	d->owner[i] = '\0';

	d->age = age;

	return (d);
}
