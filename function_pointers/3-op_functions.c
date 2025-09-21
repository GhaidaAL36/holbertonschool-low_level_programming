#include "3-calc.h"

/**
 * op_add - adds two integers
 * @a: first number
 * @b: second number
 *
 * Description: Returns the sum of a and b.
 * Return: sum of a and b
 */
int op_add(int a, int b)
{
	return (a + b);
}

/**
 * op_sub - subtracts two integers
 * @a: first number
 * @b: second number
 *
 * Description: Returns the difference a - b.
 * Return: difference of a and b
 */
int op_sub(int a, int b)
{
	return (a - b);
}

/**
 * op_mul - multiplies two integers
 * @a: first number
 * @b: second number
 *
 * Description: Returns the product of a and b.
 * Return: product of a and b
 */
int op_mul(int a, int b)
{
	return (a * b);
}

/**
 * op_div - divides two integers
 * @a: first number
 * @b: second number
 *
 * Description: Returns the result of a / b.
 * Return: quotient of a and b
 */
int op_div(int a, int b)
{
	return (a / b);
}

/**
 * op_mod - remainder of division of two integers
 * @a: first number
 * @b: second number
 *
 * Description: Returns the remainder of a / b.
 * Return: remainder of a and b
 */
int op_mod(int a, int b)
{
	return (a % b);
}
