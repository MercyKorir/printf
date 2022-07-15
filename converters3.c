#include "main.h"

unsigned int _S(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);
unsigned int _p(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len);

/**
 * _p - conv arg to hex and stores to buffer
 * @output: struct
 * @ap: arg
 * @flag: flag
 * @width: width
 * @precision: precision
 * @len: length
 *
 * Return: no of bytes stored
 */

unsigned int _p(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int addr;
	unsigned int ret = 0;

	(void)len;
	addr = va_arg(ap, unsigned long int);
	if (addr == '\0')
		return (_memcpy(output, null, 5));
	flag |= 32;
	ret += _ubase(output, addr, "0123456789abcdef", flag, width, precision);
	ret += neg_width(output, ret, flag, width);
	return (ret);
}

/**
 * _S - convarg to str then stores to buffer
 * @ap: arg
 * @flag: flag
 * @output: struct
 * @width: width
 * @precision: prec
 * @len: length
 *
 * Return: number of bytes store tobuf
 */
unsigned int _S(va_list ap, buffer_t *output, unsigned char flag,
		int width, int precision, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, i;
	unsigned int ret = 0;

	(void)len;
	str = va_arg(ap, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));
	for (size = 0; str[size]; )
		size++;
	ret += string_width(output, flag, width, precision, size);
	precision = (precision == -1) ? size : precision;
	for (i = 0; *(str + i) != '\0' && i < precision; i++)
	{
		if (*(str + i) < 32 || *(str + i) >= 127)
		{
			ret += _memcpy(output, hex, 2);
			if (*(str + i) < 16)
				ret += _memcpy(output, &zero, 1);
			ret += _ubase(output, *(str + i), "0123456789ABCDEF",
					flag, 0, 0);
			continue;
		}
		ret += _memcpy(output, (str + i), 1);
	}
	ret += neg_width(output, ret, flag, width);
	return (ret);
}
