#include "main.h"

unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *);

/**
 * _specifiers - match conversion spec to conversion fn
 * @spec: pointer to conv spec
 *
 * Return: pointer to fn or NULL
 */

unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *)
{
	int i;
	converter_t conv[] = {
		{'c', _char},
		{'s', _string},
		{'%', _perc},
		{0, NULL}
	};

	for (i = 0 ; conv[i].func ; i++)
	{
		if (conv[i].spec == *spec)
			return (conv[i].func);
	}
	return (NULL);
}

