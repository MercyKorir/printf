#include "main.h"

void clean(va_list ap, buffer_t *output);
int run(const char *format, va_list ap, buffer_t *output);
int _printf(const char *format, ...);

/**
 * clean - cleans _printf
 * @ap: arg
 * @output: struct
 */

void clean(va_list ap, buffer_t *output)
{
	va_end(ap);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * run - reads format str
 * @format: pointer
 * @ap: arg
 * @output: struct
 *
 * Return: ret
 */

int run(const char *format, va_list ap, buffer_t *output)
{
	int i, ret  = 0;
	char temp;
	unsigned char flags;
	unsigned int (*f)(va_list, buffer_t *, unsigned char);

	for (i = 0 ; *(format + i) ; i++)
	{
		if (*(format + i) == '%')
		{
			temp = 0;
			flags = _flag(format + i + 1, &temp);
			f = _specifiers(format + i + temp + 1);

			if (f != NULL)
			{
				i += temp + 1;
				ret += f(ap, output, flags);
				continue;
			}
			else if (*(format + i + temp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(output, (format + i), 1);
	}
	clean(ap, output);
	return (ret);
}

/**
 * _printf - prints str
 * @format: pointer
 *
 * Return: no. of characters
 */

int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list ap;
	int ret;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(ap, format);

	ret = run(format, ap, output);

	return (ret);
}
