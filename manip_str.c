#include "main.h"

/**
* reversed_print - prints string in reverse
* @ap: arg
* Return: characters printed
*/
int reversed_print(va_list ap)
{
	int len;
	char *str = va_arg(ap, char *);
	char *ptr = reverse_func(str);

	if (str == NULL)
		return (-1);
	if (ptr == NULL)
		return (-1);
	for (len = 0; ptr[len] != '\0'; len++)
		_putchar(ptr[len]);
	free(ptr);
	return (len);
}

/**
* rot13 - string is converted to rot13
* @ap: string to be converted
* Return: converted string
*/
int rot13(va_list ap)
{
	int n;
	int m;
	char *strva_arg(ap, char *);
	char _small[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char _upper[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	if (str == NULL)
		return (-1);
	for (m = 0; str[m] != '\0'; m++)
	{
		for (n = 0; n <= 52; n++)
		{
			if (str[m] == _small[n])
			{
				_putchar(_upper[n]);
				break;
			}
		}
		if (n == 53)
			_putchar(str[m]);
	}
	return (m);
}
