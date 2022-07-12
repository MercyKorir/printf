#include "main.h"

/**
* _address - prints address
* @ap: arg
* @func: pointer to struct
* Return: number of characters
*/
int _address(va_list ap, flags_t *func)
{
	char *str;
	unsigned long int m;
	register int i = 0;

	m = va_arg(ap, unsigned long int);
	
	(void)func;

	if (!m)
		return (_puts("(nil)"));
	str = convert(m, 16, 1);
	i += _puts("0x");
	i += _puts(str);
	return (count);
}	
