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

/**
 * struct flags - type def flag struct
 * @flag:char rep flag
 * @val: int valof flag
 */
typedef struct flags
{
	unsigned char flag;
	unsigned char value;
}flags_t;


int _printf(const char *format, ...);
int _putchar(char c);
int own_pars(const char *format, spec_t func_list[], va_list ap);
int _str(va_list);
int _char(va_list);
int _perc(va_list);
int _int(va_list);
int print_number(va_list ap);
int _binary(va_list ap);
int _octal(va_list ap);
int _hex(va_list ap);
int _upperhex(va_list ap);
int hex_check(int n, char a);
int print_reversed(va_list ap);
int rot13(va_list);
int _unsignint(va_list);
int print_unsignint(unsigned int);

/*Helper*/
unsigned int length_base(unsigned int,int);
char *reverse_func(char *str);
void _basewrite(char *s);
char *_memcpy(char *dest, char *src, unsigned int num);

#endif /*MAIN_H*/
