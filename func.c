#include "main.h"

/**
 * _char - prints char
 * @ap: list of arg
 * Return: count
 */

int _char(va_list ap)
{
	_putchar(va_arg(ap, int));
	return (1);
}

/**
 * _str - prints a string
 * @ap: argumentts
 * Retun: count
 */

int _str(va_list ap)
{
	int i;
	char *str;

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	for (i = 0 ; str[i] != '\0' ; i++)
		_putchar(str[i]);
	return (i);
}

/**
 * _perc - % symbol
 * @ap: arg
 * Return:count
 */

int _perc(__attribute__((unused))va_list ap)
{
	_putchar('%');
	return (1);
}

/**
 * _int - prints int
 * @ap: arg
 * Return: count
 */

int _int(va_list ap)
{
	int len;

	len = print_number(ap);
	return (len);
}
