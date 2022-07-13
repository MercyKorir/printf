#include "main.h"

/**
 * reverse_func - reverses str
 * @str: string to rev
 * Return: pointer to char
 */

char *reverse_func(char *str)
{
	int head;
	int temp;
	char *dest;
	int l;

	for (l = 0 ; str[l] != '\0' ; l++)
	{}

	dest = malloc(sizeof(char) * l + 1);
	if (dest == NULL)
		return (NULL);
	_memcpy(dest, str, l);
	for (head = 0 ; head < l ; head++, l--)
	{
		temp = dest[l - 1];
		dest[head] = temp;
	}
	return (dest);
}

/**
 * _basewrite - sends char to be written on stdout
 * @s: string to parse
 */

void _basewrite(char *s)
{
	int x;

	for (x = 0 ; s[x] != '\0' ; x++)
		_putchar(s[x]);
}

/**
 * length_base - length of octalnumber
 * @n: number for which lenis being calc
 * @base: base tobe calculated by
 * Return: int rep len
 */

unsigned int length_base(unsigned int n, int base)
{
	unsigned int i;

	for (i = 0 ; n > 0 ; i++)
	{
		n = n / base;
	}
	return (i);
}

/**_memcpy - cpy mem area
 * @dest: destination
 * @src: source
 * @num: number of bytes to copy
 * Return: pointer to dest
 */

char *_memcpy(char *dest, char *src, unsigned int num)
{
	unsigned int i;

	for (i = 0 ; i < num ; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
