#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

/**
* stuct spec - define structure
* @op: operator
* @func: function
*/
struct spec
{
	char *op;
	int (*func)(va_list);
};
typedef struct spec spec_t;

int _printf(const char *format, ...);
int _putchar(char c);
int own_pars(const char *format, spec_t func_list[], va_list ap);
int _str(va_list);
int _char(va_list);
int _perc(va_list);
int _int(va_list);

#endif /*MAIN_H*/
