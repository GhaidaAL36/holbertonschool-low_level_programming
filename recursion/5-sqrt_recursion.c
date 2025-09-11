#include "main.h"

/**
 * sqrt_helper - helper function to find natural square root
 * @n: number
 * @i: iterator starting from 0
 *
 * Return: natural square root or -1 if not found
 */
int sqrt_helper(int n, int i)
{
	if (i * i == n)
		return (i);
	if (i * i > n)
		return (-1);
	return (sqrt_helper(n, i + 1));
}

/**
 * _sqrt_recursion - returns natural square root of n
 * @n: number
 *
 * Return: natural square root, -1 if none
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	return (sqrt_helper(n, 0));
}
