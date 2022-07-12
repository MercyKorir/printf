#include "main.h"

/**
* _printf - produces output according to format
* @format: pointer argument
* Return: number of characters
*/
int _printf(const char *format, ...)
{
	int _charpr;
	spec_t func_list[] = {
		{"c", _char},
		{"s", _str},
		{"%", _perc},
		{"d", _int},
		{"i", _int}
	};
	va_list ap;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	_charpr = own_pars(format, func_list, ap);
	va_end(ap);
	return (_charpr);
}
