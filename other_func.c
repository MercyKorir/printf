#include <stdio.h>
#include "main.h"

/**
* _binary - converts no to binary
* @ap: arg
* Return: len
*/
int _binary(va_list ap)
{
	int j;
	int len;
	unsigned int n;
	char *str;
	char *reverse_str;

	n = va_arg(ap, unsigned int);
	if (n == 0)
		return (_putchar(48));
	if (n < 1)
		return (-1);
	len = length_base(n, 2);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (-1);
	for (j = 0; n > 0; j++)
	{
		if (n % 2 == 0)
			str[j] = '0';
		else
			str[j] = '1';
		n = n / 2;
	}
	str[j] = '\0';
	reverse_str = reverse_func(str);
	if (reverse_str == NULL)
		return (-1);
	_basewrite(reverse_str);
	free(str);
	free(reverse_str);
	return (len);
}

/**
* _octal - prints numbers in octal
* @ap: arg
* Return: total number printed
*/
int _octal(va_list list)
{
	int len;
	unsigned int n;
	char *reverse_str;
	char *repres_octal;
	
	n = v_arg(ap, unsigned int);
	if (n == 0)
		return (_putchar('0'));
	if (n < 1)
		return (-1);
	len = length_base(n, 8);

	repres_octal = malloc(sizeof(char) * len + 1);
	if (repres_octal == NULL)
		return (-1);
	for (len = 0; n > 0; len++)
	{
		repres_octal[len] = (n % 8) + 48;
		n = n / 8;
	}
	repres_octal[len] = '\0';
	reverse_str = reverse_func(repres_octal);
	if (reverse_str == NULL)
		return (-1);
	_basewrite(reverse_str);
	free(repres_octal);
	free(reverse_str);
	return (len);
}

/**
* _hex - prints number to hexadecimal
* @ap: arg
* Return: no of characters printed
*/
int _hex(va_list ap)
{
	int len;
	unsigned int n;
	int remainder_n;
	char *repres_hex;
	char *reverse_hex;

	num = va_arg(ap, unsigned int);
	if (n == 0)
		return (_putchar(48));
	if (n < 1)
		return (-1);
	len = length_base(n, 16);
	repres_hex = malloc(sizeof(char) * len + 1);
	if (repres_hex == NULL)
		return (-1);
	for (len = 0; n > 0; len++)
	{
		remainder_n = num % 16;
		if (remainder_n > 9)
		{
			remainder_n = hex_check(remainder_n, 'x');
			repres_hex[len] = remainder_n;
		}
		else
			repres_hex[len] = remainder_n +48;
		n = n / 16;
	}
	repres_hex = '\0';
	reverse_hex = reverse_func(repres_hex);
	if (reverse_hex == NULL)
		return (-1);
	_basewrite(reverse_hex);
	free(repres_hex);
	free(reverse_hex);
	return (len);
}

/**
* _upperhex = prints hexadecimal number to uppercase
* @ap: arg
* Return: characters being printed
*/
int _upperhex(va_list ap)
{
	int len;
	unsigned int n;
	char *repres_hex;
	char *reverse_hex;
	
	n = va_arg(ap, unsigned int);
	if (n == 0)
		return (_putchar('0'));
	if (n < 1)
		return (-1);
	len = length_base(n, 16);
	repres_hex = malloc(sizeof(char) * len + 1);
	if (repres_hex == NULL)
		return (-1);
	for (len = 0; n > 0; len++)
	{
		remainder_n = n % 16;
		if (remainder_n > 9)
		{
			remainder_num = hex_check(remainder_n, 'X');
			repres_hex[len] = remainder_n;
		}
		else
			repres_hex[len] = remainder_n + 48;
		n = n / 16;
	}
	repres_hex = '\0';
	reverse_hex = reverse_func(repres_hex);
	if (reverse_hex == NULL)
		return (-1);
	_basewrite(reverse_hex);
	free(repres_hex);
	free(reverse_hex);
	return (len);
}

/**
* hex_check - checks hex func to call
* @n: no to be converted
* @a: tells which func is calling it
* Return: value for letter
*/
int hex_check(int n, char a)
{
	char *hex = "abcdef";
	char _upperhex = "ABCDEF";

	n = n - 10;
	if (x == 'x')
		return (hex[n]);
	else
		return (_upperhex[n]);
	return (0);
}
