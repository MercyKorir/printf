#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* flag macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flag_s & 1)
#define SPACE_FLAG ((flag_s >> 1) & 1)
#define HASH_FLAG ((flag_s >> 2) & 1)
#define ZERO_FLAG ((flag_s >> 3) & 1)
#define NEG_FLAG ((flag_s >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2


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
} buffer_t;

/**
 * struct flag_s - typr def for flags struct
 * @flag: char repflag
 * @value: intvalof flag
 */

typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;
/**
 * struct converter_s - type def for coverter struct
 * @spec: conv spec char
 * @func: pointer to conv fn
 */

typedef struct converter_s
{
	unsigned char spec;
	unsigned int (*func)(va_list, buffer_t *);
} converter_t;

/*specifier fn*/
unsigned int _char(va_list ap, buffer_t *output);
unsigned int _string(va_list ap, buffer_t *output);
unsigned int _perc(va_list ap, buffer_t *output);
unsigned int _int(va_list ap, buffer_t *output, unsigned char len);

/* handler */
unsigned char _flag(const char *flag, char *i);
unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *, unsigned char);


/* modifier */


/* helper fn */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);

int _printf(const char *format, ...);

#endif
