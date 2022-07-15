#include "main.h"

unsigned int _sbase(buffer_t *output, long int num, char *base,
		unsigned char flag, int width, int precision);

/**
* _sbase - convert signed long to input base
* @output: struct
* @num: signed long to be convert
* @base: pointer
* @flag: flag
* @width: width
* @precision: precision
* Return: noof bytes stored to buffer
*/
unsigned int _sbase(buffer_t *output, long int num, char *base,
		unsigned char flag, int width, int precision)
{
	int size;
	char dig;
	char pad = '0';
	unsigned int ret = 1;

	for (size = 0; *(base + size);)
		size++;
	if (num >= size || num <= -size)
		ret += _sbase(output, num / size, base, flag, width - 1, precision - 1);
	else
	{
		for (; precision > 1; precision--, width--)
			ret += _memcpy(output, &pad, 1);
		if (NEG_FLAG == 0)
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				ret += _memcpy(output, &pad, 1);
		}
	}
	dig = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &dig, 1);
	return (ret);
}
