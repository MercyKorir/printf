#include "main.h"

unsigned int (*_specifiers(const char *specif))(va_list, buffer_t *, unsigned char);
unsigned char _flag(const char *flag, char *i);

/**
 * _flag - match flag with corresponding val
 * @flag: pointer
 * @i: counter fororig format str
 *
 * Return: corresponding val
 */

unsigned char _flag(const char *flag, char *i)
{
	int j, k;
	unsigned char ret = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{'-', NEG},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{0, 0}
	};

	for (j = 0 ; flag[j] ; j++)
	{
		for (k = 0 ; flags[k].flag != 0 ; k++)
		{
			if (flag[j] == flags[k].flag)
			{
				(*i)++;
				if (ret == 0)
					ret = flags[k].value;
				else
					ret |= flags[k].value;
				break;
			}
		}
		if (flags[k].value == 0)
			break;
	}
	return (ret);
}


/**
 * _specifiers - match conversion spec to conversion fn
 * @spec: pointer to conv spec
 *
 * Return: pointer to fn or NULL
 */

unsigned int (*_specifiers(const char *specif))(va_list, buffer_t *, unsigned char)
{
	int i;
	converter_t conv[] = {
		{'c', _char},
		{'s', _string},
		{'%', _perc},
		{'d', _int},
		{'i', _int},
		{0, NULL}
	};

	for (i = 0 ; conv[i].func ; i++)
	{
		if (conv[i].spec == *specif)
			return (conv[i].func);
	}
	return (NULL);
}

