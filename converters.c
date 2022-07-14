#include "main.h"

unsigned int _char(va_list ap, buffer_t *output);
unsigned int _perc(va_list ap, buffer_t *output);
unsigned int _string(va_list ap, buffer_t *output);

/**
 * _char - converts tounsigned char and stores in buffer
 * @ap: arg
 * @output: struct
 *
 * Return: no.of bytes stored in buffer
 */

unsigned int _char(va_list ap, buffer_t *output)
{
	char c;
	unsigned int ret = 0;

	c = va_arg(ap, int);
	ret += _memcpy(output, &c, 1);

	return (ret);
}

/**
 * _perc - stored % to buffer
 * @ap: arg
 * @output: struct
 *
 * Return: no . of bytes stored tobuffer
 */

unsigned int _perc(va_list ap, buffer_t *output)
{
	char percent = '%';
	unsigned int ret = 0;

	(void)ap;

	ret += _memcpy(output, &percent, 1);

	return (ret);
}

/**
 * _string - convertes arg to string and stores in buffer
 * @ap: arg
 * @output: buffer struct
 *
 * Return: no. ofbytes
 */

unsigned int _string(va_list ap, buffer_t *output)
{
	char *str;
	char *null = "(null)";
	int size;
	unsigned int ret = 0;

	str = va_arg(ap, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (size = 0 ; *(str + size) ; )
		size++;
	while (*str != '\0')
	{
		ret += _memcpy(output, str, 1);
		str++;
	}
	return (ret);
}
