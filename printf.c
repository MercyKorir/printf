#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * _printf - produces output acc toformat
 * @format: pointer
 *
 * Return: total number of characters excluding \0
 */

int _printf(const char *format, ...)
{
	int n;
	int total = 0;
	bool flag = false;
	va_list ap;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	for (n = 0 ; *(format + n) != '\0' ; n++)
	{
		if (format[n] == '%')
			flag = true;
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
					total += print_string(va_arg(ap, char *));
					break;
				case '%':
					_putchar('%');
					total += 1;
					break;
				case 'd':
					total += print_int(va_arg(ap, int));
					break;
				case 'i':
					total += print_int(va_arg(ap, int));
					break;
				default:
					_putchar('%');
					_putchar(format[n]);
					total += 2;
			};
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
