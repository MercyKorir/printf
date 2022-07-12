#include "main.h"

/**
 * own_pars - receives main and parameters to print formated string
 * @format: pointer to string
 * @func_list: list of all possible specifiers
 * @ap: list of arg passed
 * Return: count
 */

int own_pars(const char *format, spec_t func_list[], va_list ap)
{
	int i, j, val, _charpr;

	_charpr = 0;
	for (i = 0 ; format[i] != '\0' ; i++)
	{
		if (format[i] == '%')
		{
			for (j = 0 ; func_list[j].op != NULL; j++)
			{
				if (format[i + 1] == func_list[j].op[0])
				{
					val = func_list[j].func(ap);
					if (val == -1)
						return (-1);
					_charpr += val;
					break;
				}
			}
			if (func_list[j].op == NULL && format[i + 1] != ' ')
			{
				if (format[i + 1] != '\0')
				{
					_putchar(format[i]);
					_putchar(format[i + 1]);
					_charpr += 2;
				}
				else
					return (-1);
			}
			i = i + 1;
		}
		else
		{
			_putchar(format[i]);
			_charpr++;
		}
	}
	return (_charpr);
}
