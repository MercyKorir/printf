#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct buffer_s - type def buffer struct
 * @buffer: char array pointer
 * @start: start buffer pointer
 * @len: length
 */

typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
}buffer_t;

/**
 * struct converter_s - type def for coverter struct
 * @spec: conv spec char
 * @func: pointer to conv fn
 */

typedef struct converter_s
{
	unsigned char spec;
	unsigned int (*func)(va_list, buffer_t *);
}converter_t;

/*specifier fn*/
unsigned int _char(va_list ap, buffer_t *output);
unsigned int _string(va_list ap, buffer_t *output);
unsigned int _perc(va_list ap, buffer_t *output);

/* handler */
unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *);


/* modifier */


/* helper fn */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);

int _printf(const char *format, ...);

#endif
