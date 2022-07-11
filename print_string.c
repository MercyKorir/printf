#include <stdio.h>
#include "main.h"

/**
* print_string - printd a string
* @str: string to be printed
* Return: returns length
*/
int print_string(char *str)
{
	int len;

	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		_putchar(*str++);
		len++;
	}
	return (len);
}
