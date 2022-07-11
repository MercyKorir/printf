#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/**
* _printf - produces output according to format
* @format: first arg
* Return: total number of characters.
*/
int _printf(const char *format, ...)
{
	int n;
	bool flag;
	int total = 0;

	va_list ap;
	
	flag = false;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	
	for (n = 0; *(format + n) != '\0'; n++)
	{
		if (format[n] == '%')
		{
			flag = true;
		}
		else if (flag == true)
		{
			flag = false;

			switch (format[n])
			{
				case 'c':
					_putchar(va_arg(ap, int));
					total += 1;
					break;
				case 's':
					print_string(va_arg(ap, char));
					total += 1;
					break;
				case '%':
					_putchar('%');
					total += 1;
					break;
				default:
					_putchar('%');
					_putchar(format[n]);
					total += 2;
			}
		}
		else
		{
			_putchar(format[n]);
			total += 1;
		}
	}
	va_end(ap);
	return (total);
}
