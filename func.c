#include "main.h"
#include <stdio.h>

int print_string(char *str);
int print_int(int num);


/**
 * print_string - prints string
 * @str: string to be printed
 *
 * Return: len
 */

int print_string(char *str)
{
	int len;

	if (str == NULL)
		return (0);
	while (*str)
	{
		_putchar(*str++);
		len++;
	}
	return (len);
}

/**
 * print_int - prints integer
 * @num: int tobe printed
 * Return: count
 */


int print_int(int num)
{
	int count = 0;

	if (num < 0)
	{
		_putchar('-');
		num = -num;
		count += 1;
	}
	if (num > 9)
		count += print_int(num / 10);
	_putchar((num % 10) + '0');
	count += 1;
	return (count);
}
