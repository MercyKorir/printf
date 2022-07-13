#include "main.h"

/**
 * _bigS - non printable char
 * @ap: arg
 * @t: pointer to struct flaf
 * Return:count
 */

int _bigS(va_list ap, flags_t *t)
{
	int i, count = 0;
	char *r;
	char *s = va_arg(ap, char *);

	(void)t;
	if (!s)
		return (_puts("(null)"));
	for (i = 0 ; s[i] ; i++)
	{
		if (s[i] > 0 && (s[i] < 32  || s[i] >= 127))
		{
			_puts("\\x");
			count += 2;
			r = convert(s[i], 16, 0);
			if (!r[1])
				count += _putchar('0');
			count += _puts(r);
		}
		else
			count += _putchar(s[i]);
	}
	return (count);
}

/**
 * _rev - reverse str
 * @ap: arg
 * @t: pointer to struct flags
 * Return: len
 */

int _rev(va_list ap, flags_t *t)
{
	int i = 0, j;
	char *s = va_arg(ap, char *s);

	(void)t;
	if (!s)
		s = "(null)";
	while (S[i])
		i++;
	for (j = i - 1 ; j >= 0 ; j--)
		_putchar(s[j]);
	return (i);
}

/**
 * _rot13 - uses rot13
 * @ap: arg
 * @t: pointer to struct flags
 * Return: len
 */

int _rot13(va_list ap, flags_t *t)
{
	int i, j;
	char rot13[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char ROT13[] = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *s = va_arg(l, char *);

	(void)t;
	for (j = 0 ; s[j] ; j++)
	{
		if (s[j] < 'A' || (s[j] > 'Z' && s[j] < 'a') || s[j] > 'z')
			_putchar(s[j]);
		else
		{
			for (i = 0 ; i <= 52 ; i++)
			{
				if (s[j] == rot13[i])
					_putchar(ROT13[i]);
			}
		}
	}
	return (j);
}

/**
 * _percent - %
 * @ap: arg
 * @t: pointer to struct
 * Return: char
 */

int _percent(va_list ap, flags_t *t)
{
	(void)ap;
	(void)t;
	return (_putchar('%'));
}
