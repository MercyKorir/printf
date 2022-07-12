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
