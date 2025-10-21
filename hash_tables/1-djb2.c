/**
 * hash_djb2 - Generates a hash value using the djb2 algorithm.
 * @str: The string to hash.
 *
 * Description: Implements the djb2 algorithm by
 * initializing the hash to 5381 and then iterating
 * through each character of the string, updating
 * the hash value with hash * 33 + current_char.
 *
 * Return: The computed hash value as an unsigned long int.
*/
unsigned long int hash_djb2(const unsigned char *str)
{
	unsigned long int hash;
	int c;

	hash = 5381;
	while ((c = *str++))
	{
	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return (hash);
}
