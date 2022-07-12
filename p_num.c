#include "main.h"

/**
 * print_number - prints num
 * @ap: arg
 * Return: count
 */

int print_number(va_list ap)
{
	int i = va_arg(ap, int);
	int len = 0;
	unsigned int num;
	int div = 1;

	if (i < 0)
	{
		len += _putchar('-');
		num = i * - 1;
	}
	else
		num = i;
	for (; num / div > 9 ; )
		div *= 10;
	for (; div != 0 ; )
	{
		len += _putchar(48 + num / div);
		num %= div;
		div /= 10;
	}
	return (len);
}

/**
* print_unsignint - prints unsigned int
* @i: unsigned int to be printed
* Return: total numbers printed
*/
int print_unsignint(unsigned int i)
{
	int len = 0;
	int div = 1;
	unsigned int n = i;

	for (; n / div > 9; )
		div *= 10;
	for (; div != 0; )
	{
		len += _putchar(48 + n / div);
		n %= div;
		div /= 10;
	}
	return (len);
}
