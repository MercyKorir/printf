#include "main.h"
#include <stdio.h>

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
