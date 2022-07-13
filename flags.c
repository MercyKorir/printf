#include "main.h"

/**
 * g_flag - turns on flags if printf 
 * finds flag mod in format str
 * @c: char that holds flag spec
 * @t: pointer to struct flags
 * Return: 1 if flag has been turnedon
 */

int g_flag(char c, flags_t *t)
{
	int i = 0;

	switch (c)
	{
		case '+':
			t->plus = 1;
			i = 1;
			break;
		case ' ':
			t->space = 1;
			i = 1;
			break;
		case '#':
			t->hash = 1;
			i = 1;
			break;
	}
	return (i);
}
