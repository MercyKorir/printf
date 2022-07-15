#include "main.h"

unsigned int _char(va_list ap, buffer_t *output);
unsigned int _perc(va_list ap, buffer_t *output);
unsigned int _string(va_list ap, buffer_t *output);
unsigned int _int (va_list ap, buffer_t *output, unsigned char flag);

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

/**
 * _int - converts to signed int and stores in buffer
 * @ap: arg
 * @output: struct
 *
 * Return: bytes stored
 */

unsigned int _int(va_list ap, buffer_t *output, unsigned char flag)
{
	long int d;
	unsigned int ret = 0;
	unsigned int count = 0;
	char space = ' ';
	char neg = '-';
	char plus = '+';


	d = va_arg(ap, int);
	
	/* space flag */
	if (SPACE_FLAG == 1 && d >= 0)
		ret += _memcpy(output, &space, 1);
	if (NEG_FLAG == 0)
	{
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;

		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(output, &plus, 1);
		if  (ZERO_FLAG == 1 && d < 0)
			ret += _memcpy(output, &neg, 1);

	}
	if (ZERO_FLAG == 0 && d < 0)
		ret += _memcpy(output, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(output, &plus, 1);
	return (ret);
}
