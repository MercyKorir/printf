#include "main.h"

/**
 * main - Entry point for testing _printf
 *
 * Return: Always 0
 */
int main(void)
{
	int len;

	/* Header */
	_printf("\n");
	_printf("╔════════════════════════════════════════════════════════╗\n");
	_printf("║       Custom Printf Implementation Test Suite         ║\n");
	_printf("╚════════════════════════════════════════════════════════╝\n");
	_printf("\n");

	/* Basic tests */
	_printf("┌─ BASIC TESTS ─────────────────────────────────────────┐\n");
	len = _printf("Hello, World!\n");
	_printf("Length of 'Hello, World!': %d\n", len);
	_printf("\n");

	/* Character tests */
	_printf("┌─ CHARACTER TESTS ─────────────────────────────────────┐\n");
	_printf("Single char 'A': %c\n", 'A');
	_printf("Single char 'Z': %c\n", 'Z');
	_printf("Single char '0': %c\n", '0');
	_printf("Single char '@': %c\n", '@');
	_printf("\n");

	/* String tests */
	_printf("┌─ STRING TESTS ────────────────────────────────────────┐\n");
	_printf("Simple string: %s\n", "Hello, WSL Ubuntu!");
	_printf("Empty string: '%s'\n", "");
	_printf("NULL string: '%s'\n", NULL);
	_printf("\n");

	/* Percent sign */
	_printf("┌─ PERCENT SIGN TEST ───────────────────────────────────┐\n");
	_printf("Percent sign: 100%% complete\n");
	_printf("Multiple: %% %% %%\n");
	_printf("\n");

	/* Integer tests */
	_printf("┌─ INTEGER TESTS ───────────────────────────────────────┐\n");
	_printf("Positive integer: %d\n", 42);
	_printf("Negative integer: %d\n", -42);
	_printf("Zero: %d\n", 0);
	_printf("Large positive: %d\n", 2147483647);
	_printf("Large negative: %d\n", -2147483648);
	_printf("Using %%i: %i\n", 98);
	_printf("\n");

	/* Unsigned integer tests */
	_printf("┌─ UNSIGNED INTEGER TESTS ──────────────────────────────┐\n");
	_printf("Unsigned: %u\n", 123456);
	_printf("Unsigned zero: %u\n", 0);
	_printf("Max unsigned: %u\n", 4294967295u);
	_printf("\n");

	/* Binary tests */
	_printf("┌─ BINARY TESTS ────────────────────────────────────────┐\n");
	_printf("Binary of 0: %b\n", 0);
	_printf("Binary of 1: %b\n", 1);
	_printf("Binary of 42: %b\n", 42);
	_printf("Binary of 255: %b\n", 255);
	_printf("Binary of 1024: %b\n", 1024);
	_printf("\n");

	/* Octal tests */
	_printf("┌─ OCTAL TESTS ─────────────────────────────────────────┐\n");
	_printf("Octal of 8: %o\n", 8);
	_printf("Octal of 64: %o\n", 64);
	_printf("Octal of 255: %o\n", 255);
	_printf("Octal with # flag: %#o\n", 64);
	_printf("Octal of zero: %o\n", 0);
	_printf("\n");

	/* Hexadecimal tests */
	_printf("┌─ HEXADECIMAL TESTS ───────────────────────────────────┐\n");
	_printf("Lowercase hex of 255: %x\n", 255);
	_printf("Uppercase hex of 255: %X\n", 255);
	_printf("Hex with # flag (lower): %#x\n", 255);
	_printf("Hex with # flag (upper): %#X\n", 255);
	_printf("Hex of zero: %x\n", 0);
	_printf("Hex of 4096: %x\n", 4096);
	_printf("\n");

	/* Pointer tests */
	_printf("┌─ POINTER TESTS ───────────────────────────────────────┐\n");
	{
		int num = 10;
		char *str = "test";
		_printf("Pointer to int: %p\n", (void *)&num);
		_printf("Pointer to string: %p\n", (void *)str);
		_printf("NULL pointer: %p\n", NULL);
	}
	_printf("\n");

	/* Flag tests - Plus */
	_printf("┌─ PLUS FLAG TESTS ─────────────────────────────────────┐\n");
	_printf("Positive with +: %+d\n", 42);
	_printf("Negative with +: %+d\n", -42);
	_printf("Zero with +: %+d\n", 0);
	_printf("\n");

	/* Flag tests - Space */
	_printf("┌─ SPACE FLAG TESTS ────────────────────────────────────┐\n");
	_printf("Positive with space: % d\n", 42);
	_printf("Negative with space: % d\n", -42);
	_printf("Zero with space: % d\n", 0);
	_printf("\n");

	/* Flag tests - Hash */
	_printf("┌─ HASH FLAG TESTS ─────────────────────────────────────┐\n");
	_printf("Hex with #: %#x\n", 255);
	_printf("Hex with #: %#X\n", 255);
	_printf("Octal with #: %#o\n", 64);
	_printf("Zero with #: %#x\n", 0);
	_printf("\n");

	/* Flag tests - Zero padding */
	_printf("┌─ ZERO PADDING TESTS ──────────────────────────────────┐\n");
	_printf("Zero padded: %05d\n", 42);
	_printf("Zero padded negative: %05d\n", -42);
	_printf("Zero padded hex: %08x\n", 255);
	_printf("\n");

	/* Width tests */
	_printf("┌─ WIDTH TESTS ─────────────────────────────────────────┐\n");
	_printf("Width 10, right: |%10d|\n", 42);
	_printf("Width 10, left: |%-10d|\n", 42);
	_printf("Width 15, string: |%15s|\n", "Hello");
	_printf("Width 15, left string: |%-15s|\n", "Hello");
	_printf("\n");

	/* Precision tests */
	_printf("┌─ PRECISION TESTS ─────────────────────────────────────┐\n");
	_printf("Precision 5: %.5d\n", 42);
	_printf("Precision 8: %.8d\n", 42);
	_printf("Precision with negative: %.5d\n", -42);
	_printf("String precision 3: %.3s\n", "Hello World");
	_printf("\n");

	/* Combined width and precision */
	_printf("┌─ WIDTH + PRECISION TESTS ─────────────────────────────┐\n");
	_printf("Width 10, precision 5: |%10.5d|\n", 42);
	_printf("Width 15, precision 3: |%15.3s|\n", "Hello World");
	_printf("\n");

	/* Length modifier tests */
	_printf("┌─ LENGTH MODIFIER TESTS ───────────────────────────────┐\n");
	_printf("Short int: %hd\n", (short)42);
	_printf("Long int: %ld\n", 1234567890L);
	_printf("Long unsigned: %lu\n", 4294967295UL);
	_printf("\n");

	/* Special converter tests */
	_printf("┌─ SPECIAL CONVERTER TESTS ─────────────────────────────┐\n");
	_printf("Reversed string: %r\n", "Hello World");
	_printf("ROT13 encoded: %R\n", "Hello World");
	_printf("Non-printable chars: %S\n", "Hello\nWorld\x01\x7F");
	_printf("\n");

	/* Mixed format tests */
	_printf("┌─ MIXED FORMAT TESTS ──────────────────────────────────┐\n");
	_printf("Name: %s, Age: %d, Score: %u\n", "Alice", 25, 95);
	_printf("Hex: 0x%x, Oct: 0%o, Bin: 0b%b\n", 255, 64, 42);
	_printf("Flags: %+d, % d, %#x, %05d\n", 42, 42, 255, 42);
	_printf("\n");

	/* Edge cases */
	_printf("┌─ EDGE CASE TESTS ─────────────────────────────────────┐\n");
	_printf("Empty format string\n");
	_printf("No specifiers in this string\n");
	_printf("INT_MAX: %d\n", 2147483647);
	_printf("INT_MIN: %d\n", -2147483648);
	_printf("Multiple specifiers: %d %s %c %x\n", 42, "test", 'A', 255);
	_printf("\n");

	/* Performance indicator */
	_printf("┌─ TEST COMPLETE ───────────────────────────────────────┐\n");
	_printf("All tests executed successfully!\n");
	_printf("\n");

	return (0);
}