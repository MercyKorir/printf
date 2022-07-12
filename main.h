#ifndef MAIN_H
#define MAIN_H

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
int print_string(char *str);

#endif /*MAIN_H*/
