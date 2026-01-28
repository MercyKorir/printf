# API Reference - Custom Printf

## Table of Contents

- [Core API](#core-api)
- [Public Functions](#public-functions)
- [Internal Functions](#internal-functions)
- [Data Structures](#data-structures)
- [Macros and Constants](#macros-and-constants)
- [Format Specifiers](#format-specifiers)
- [Return Values](#return-values)
- [Error Handling](#error-handling)
- [Usage Examples](#usage-examples)

---

## Core API

### _printf

**Prototype:**
```c
int _printf(const char *format, ...);
```

**Description:**  
Produces output according to a format string. This is the main entry point for formatted output, mimicking the behavior of the standard C `printf` function.

**Parameters:**
- `format` - A null-terminated format string containing literal text and format specifiers

**Returns:**
- On success: Number of characters printed (excluding null byte)
- On error: `-1`

**Format String Syntax:**
```
%[flags][width][.precision][length]specifier
```

**Example:**
```c
#include "main.h"

int main(void)
{
    int count;
    
    count = _printf("Hello, %s! The number is %d\n", "World", 42);
    _printf("Printed %d characters\n", count);
    
    return (0);
}
```

---

## Public Functions

All user-facing functionality is accessed through the `_printf` function. Other functions are internal implementation details.

---

## Internal Functions

### Buffer Management (helpers.c)

#### init_buffer

**Prototype:**
```c
buffer_t *init_buffer(void);
```

**Description:**  
Allocates and initializes a new output buffer structure with a 1024-byte internal buffer.

**Returns:**
- Pointer to initialized `buffer_t` structure
- `NULL` on allocation failure

**Memory:**  
Caller must call `free_buffer()` to release memory.

---

#### _memcpy

**Prototype:**
```c
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
```

**Description:**  
Copies `n` bytes from `src` into the output buffer. Automatically flushes to stdout when buffer reaches 1024 bytes.

**Parameters:**
- `output` - Pointer to buffer structure
- `src` - Source data to copy
- `n` - Number of bytes to copy

**Returns:**  
Number of bytes copied (`n`)

**Side Effects:**  
May trigger buffer flush via `write(1, ...)` system call.

---

#### free_buffer

**Prototype:**
```c
void free_buffer(buffer_t *output);
```

**Description:**  
Frees all memory associated with a buffer structure.

**Parameters:**
- `output` - Buffer to free

**Returns:**  
None (void)

---

### Format String Parsing (handlers.c)

#### _flag

**Prototype:**
```c
unsigned char _flag(const char *flag, char *i);
```

**Description:**  
Parses flag characters from format string and returns a bitmask of enabled flags.

**Recognized Flags:**
- `+` - Always show sign for signed numbers (PLUS)
- `-` - Left-justify within field width (NEG)
- ` ` - Prefix space before positive numbers (SPACE)
- `#` - Alternate form (0x for hex, 0 for octal) (HASH)
- `0` - Zero-pad numeric values (ZERO)

**Parameters:**
- `flag` - Pointer to first character after '%'
- `i` - Pointer to index counter (incremented for each flag found)

**Returns:**  
Bitmask of flags (unsigned char)

**Example:**
```c
char index = 0;
unsigned char flags = _flag("+0", &index);
/* flags will contain (PLUS | ZERO), index will be 2 */
```

---

#### _width

**Prototype:**
```c
int _width(va_list ap, const char *modifier, char *i);
```

**Description:**  
Parses minimum field width from format string. Supports both numeric and `*` (dynamic) width.

**Parameters:**
- `ap` - Variable argument list (for `*` width)
- `modifier` - Pointer to format string position
- `i` - Pointer to index counter

**Returns:**
- Parsed width value
- `0` if width ≤ 0 or not specified

**Example:**
```c
/* "%10d" -> returns 10 */
/* "%*d" with arg 15 -> returns 15 */
/* "%-d" -> returns 0 */
```

---

#### _precision

**Prototype:**
```c
int _precision(va_list ap, const char *modifier, char *i);
```

**Description:**  
Parses precision specifier from format string. Precision must start with `.`

**Parameters:**
- `ap` - Variable argument list (for `*` precision)
- `modifier` - Pointer to format string position
- `i` - Pointer to index counter

**Returns:**
- Parsed precision value
- `-1` if no precision specified
- `0` for bare `.` or precision ≤ 0

**Example:**
```c
/* "%.5d" -> returns 5 */
/* "%.*d" with arg 3 -> returns 3 */
/* "%.d" -> returns 0 */
/* "%d" -> returns -1 */
```

---

#### _length

**Prototype:**
```c
unsigned char _length(const char *modifier, char *i);
```

**Description:**  
Parses length modifier from format string.

**Supported Modifiers:**
- `h` - Short (SHORT = 1)
- `l` - Long (LONG = 2)

**Parameters:**
- `modifier` - Pointer to format string position
- `i` - Pointer to index counter

**Returns:**
- `SHORT` (1) for 'h'
- `LONG` (2) for 'l'
- `0` for no modifier

---

#### _specifiers

**Prototype:**
```c
unsigned int (*_specifiers(const char *spec))(
    va_list, buffer_t *, unsigned char, int, int, unsigned char);
```

**Description:**  
Maps conversion specifier character to its handler function.

**Parameters:**
- `spec` - Pointer to specifier character

**Returns:**
- Function pointer to appropriate converter
- `NULL` if specifier not recognized

**Supported Specifiers:**
| Char     | Function  | Description         |
|----------|-----------|---------------------|
| `c`      | _char     | Character           |
| `s`      | _string   | String              |
| `%`      | _perc     | Literal %           |
| `d`, `i` | _int      | Signed decimal      |
| `b`      | _bin      | Binary              |
| `u`      | _dec      | Unsigned decimal    |
| `o`      | _oct      | Octal               |
| `x`      | lower_hex | Hex lowercase       |
| `X`      | upper_hex | Hex uppercase       |
| `S`      | _S        | String with escapes |
| `p`      | _p        | Pointer             |
| `r`      | _r        | Reversed string     |
| `R`      | _R        | ROT13 encoded       |

---

### Width and Padding (modifiers.c)

#### print_width

**Prototype:**
```c
unsigned int print_width(buffer_t *output, unsigned int printed,
                         unsigned char flag, int width);
```

**Description:**  
Inserts leading spaces (or zeros) to satisfy minimum field width when right-justifying.

**Parameters:**
- `output` - Buffer structure
- `printed` - Characters already printed
- `flag` - Flag bitmask
- `width` - Minimum field width

**Returns:**  
Number of padding characters inserted

**Behavior:**
- Only pads if NEG_FLAG is not set (not left-justified)
- Uses space or '0' based on ZERO_FLAG

---

#### string_width

**Prototype:**
```c
unsigned int string_width(buffer_t *output, unsigned char flag,
                          int width, int precision, int size);
```

**Description:**  
Handles leading padding for string conversions, considering both width and precision.

**Parameters:**
- `output` - Buffer structure
- `flag` - Flag bitmask
- `width` - Minimum field width
- `precision` - Maximum characters to print (-1 for no limit)
- `size` - Actual string length

**Returns:**  
Number of padding characters inserted

---

#### neg_width

**Prototype:**
```c
unsigned int neg_width(buffer_t *output, unsigned int printed,
                       unsigned char flag, int width);
```

**Description:**  
Inserts trailing spaces when left-justifying (NEG_FLAG set).

**Parameters:**
- `output` - Buffer structure
- `printed` - Characters already printed
- `flag` - Flag bitmask
- `width` - Minimum field width

**Returns:**  
Number of padding characters inserted

---

### Base Conversion (base.c)

#### _sbase

**Prototype:**
```c
unsigned int _sbase(buffer_t *output, long int num, char *base,
                    unsigned char flag, int width, int precision);
```

**Description:**  
Recursively converts a signed long integer to any base representation.

**Parameters:**
- `output` - Buffer structure
- `num` - Number to convert
- `base` - String of digit characters (e.g., "0123456789" for decimal)
- `flag` - Flag bitmask
- `width` - Minimum field width
- `precision` - Minimum digits to print

**Returns:**  
Number of bytes written to buffer

**Example:**
```c
/* Decimal: base = "0123456789" */
/* Binary: base = "01" */
/* Hex: base = "0123456789abcdef" */
```

---

#### _ubase

**Prototype:**
```c
unsigned int _ubase(buffer_t *output, unsigned long int num, char *base,
                    unsigned char flag, int width, int precision);
```

**Description:**  
Recursively converts an unsigned long integer to any base representation. Handles HASH_FLAG for prefix (0x, 0X).

**Parameters:**
- `output` - Buffer structure
- `num` - Number to convert
- `base` - String of digit characters
- `flag` - Flag bitmask (bit 5 controls 0x prefix)
- `width` - Minimum field width
- `precision` - Minimum digits to print

**Returns:**  
Number of bytes written to buffer

---

## Data Structures

### buffer_t

**Definition:**
```c
typedef struct buffer_s
{
    char *buffer;           /* Current write position */
    char *start;            /* Start of buffer memory */
    unsigned int len;       /* Bytes currently in buffer */
} buffer_t;
```

**Purpose:**  
Manages a 1024-byte output buffer for efficient I/O operations.

**Fields:**
- `buffer` - Points to next write position
- `start` - Points to beginning of allocated buffer
- `len` - Number of bytes currently buffered (0-1024)

**Lifecycle:**
1. Created with `init_buffer()`
2. Data written via `_memcpy()`
3. Auto-flushes at 1024 bytes
4. Final flush in `clean()` function
5. Freed with `free_buffer()`

---

### flag_t

**Definition:**
```c
typedef struct flag_s
{
    unsigned char flag;     /* Flag character (+, -, space, #, 0) */
    unsigned char value;    /* Corresponding bitmask value */
} flag_t;
```

**Purpose:**  
Maps flag characters to their bit values in the `_flag()` function.

---

### converter_t

**Definition:**
```c
typedef struct converter_s
{
    unsigned char spec;     /* Specifier character (c, s, d, etc.) */
    unsigned int (*func)(va_list, buffer_t *, unsigned char,
                         int, int, unsigned char);
} converter_t;
```

**Purpose:**  
Maps conversion specifier characters to their handler functions in `_specifiers()`.

---

## Macros and Constants

### Flag Macros

**Definition:**
```c
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16

#define PLUS_FLAG (flag & 1)
#define SPACE_FLAG ((flag >> 1) & 1)
#define HASH_FLAG ((flag >> 2) & 1)
#define ZERO_FLAG ((flag >> 3) & 1)
#define NEG_FLAG ((flag >> 4) & 1)
```

**Usage:**
```c
unsigned char flags = PLUS | ZERO;  /* Both + and 0 flags set */

if (PLUS_FLAG)
    /* Handle plus flag */
```

---

### Length Modifier Macros

**Definition:**
```c
#define SHORT 1
#define LONG 2
```

**Usage:**
```c
if (len == LONG)
    value = va_arg(ap, long int);
else if (len == SHORT)
    value = (short)va_arg(ap, int);
```

---

## Format Specifiers

### Complete Format String Syntax

```
%[flags][width][.precision][length]specifier
```

### Specifier Details

| Specifier | Type | Length | Description | Example | Output |
|-----------|------|--------|-------------|---------|--------|
| `%c` | char | - | Single character | `_printf("%c", 'A')` | `A` |
| `%s` | char* | - | String | `_printf("%s", "Hi")` | `Hi` |
| `%d` | int | h, l | Signed decimal | `_printf("%d", -42)` | `-42` |
| `%i` | int | h, l | Signed decimal | `_printf("%i", 42)` | `42` |
| `%u` | unsigned | h, l | Unsigned decimal | `_printf("%u", 100)` | `100` |
| `%o` | unsigned | h, l | Octal | `_printf("%o", 8)` | `10` |
| `%x` | unsigned | h, l | Hex (lower) | `_printf("%x", 255)` | `ff` |
| `%X` | unsigned | h, l | Hex (upper) | `_printf("%X", 255)` | `FF` |
| `%b` | unsigned | - | Binary (custom) | `_printf("%b", 5)` | `101` |
| `%p` | void* | - | Pointer | `_printf("%p", ptr)` | `0x7fff...` |
| `%r` | char* | - | Reverse (custom) | `_printf("%r", "Hi")` | `iH` |
| `%R` | char* | - | ROT13 (custom) | `_printf("%R", "Hi")` | `Uv` |
| `%S` | char* | - | Escaped (custom) | `_printf("%S", "A\x01")` | `A\x01` |
| `%%` | - | - | Literal % | `_printf("%%")` | `%` |

---

## Return Values

### Success

`_printf` returns the number of characters printed (excluding the null byte terminator).

```c
int count = _printf("Hello"); /* Returns 5 */
```

### Error Conditions

Returns `-1` in the following cases:
- `format` is `NULL`
- Buffer allocation fails (`init_buffer` returns `NULL`)
- Format string ends with incomplete format specifier (e.g., "test %")

---

## Error Handling

### NULL Pointer Handling

```c
/* NULL format string */
_printf(NULL);              /* Returns -1 */

/* NULL string argument */
_printf("%s", NULL);        /* Prints "(null)", returns 6 */

/* NULL pointer */
_printf("%p", NULL);        /* Prints "(nil)", returns 5 */
```

### Buffer Allocation Failure

If `init_buffer()` fails (returns NULL), `_printf` returns `-1` without attempting to print.

### Incomplete Format Specifiers

If format string ends with `%` without a specifier:
```c
_printf("test %");          /* Returns -1 */
```

---

## Usage Examples

### Basic Formatting

```c
#include "main.h"

int main(void)
{
    /* Characters and strings */
    _printf("Character: %c\n", 'X');
    _printf("String: %s\n", "Hello, World!");
    _printf("Percent: %%\n");
    
    /* Numbers in different bases */
    _printf("Decimal: %d\n", 42);
    _printf("Hex: %x\n", 255);
    _printf("Octal: %o\n", 8);
    _printf("Binary: %b\n", 5);
    
    return (0);
}
```

### Width and Precision

```c
#include "main.h"

int main(void)
{
    /* Width */
    _printf("|%10s|\n", "Hi");      /* |        Hi| */
    _printf("|%-10s|\n", "Hi");     /* |Hi        | */
    _printf("|%10d|\n", 42);        /* |        42| */
    
    /* Precision */
    _printf("%.3s\n", "Hello");     /* Hel */
    _printf("%.5d\n", 42);          /* 00042 */
    
    /* Width + Precision */
    _printf("|%10.5d|\n", 42);      /* |     00042| */
    
    return (0);
}
```

### Flags

```c
#include "main.h"

int main(void)
{
    /* Plus flag */
    _printf("%+d\n", 42);           /* +42 */
    _printf("%+d\n", -42);          /* -42 */
    
    /* Space flag */
    _printf("% d\n", 42);           /*  42 */
    
    /* Hash flag */
    _printf("%#x\n", 255);          /* 0xff */
    _printf("%#X\n", 255);          /* 0XFF */
    _printf("%#o\n", 8);            /* 010 */
    
    /* Zero padding */
    _printf("%05d\n", 42);          /* 00042 */
    _printf("%08x\n", 255);         /* 000000ff */
    
    return (0);
}
```

### Length Modifiers

```c
#include "main.h"

int main(void)
{
    /* Short */
    _printf("%hd\n", (short)42);
    
    /* Long */
    _printf("%ld\n", 123456789L);
    _printf("%lu\n", 4294967295UL);
    _printf("%lx\n", 0xFFFFFFFFL);
    
    return (0);
}
```

### Custom Specifiers

```c
#include "main.h"

int main(void)
{
    int num = 42;
    
    /* Reversed string */
    _printf("%r\n", "Hello");       /* olleH */
    
    /* ROT13 encoding */
    _printf("%R\n", "Hello");       /* Uryyb */
    
    /* Escaped non-printables */
    _printf("%S\n", "Hi\nWorld");   /* Hi\x0AWorld */
    
    /* Pointer address */
    _printf("%p\n", (void *)&num);  /* 0x7ffe... */
    
    return (0);
}
```

---

## Performance Considerations

### Buffer Size

The 1024-byte buffer reduces system calls:
- Unbuffered: 1 `write()` call per character
- Buffered: 1 `write()` call per 1024 characters

### Memory Usage

- Buffer structure: ~16 bytes
- Buffer itself: 1024 bytes
- Total: ~1040 bytes per `_printf` call

### Recursion Depth

Base conversion functions (`_sbase`, `_ubase`) use recursion. Maximum depth:
- Binary: log₂(num) (e.g., 64 for 64-bit numbers)
- Decimal: log₁₀(num) (e.g., 20 for 64-bit numbers)
- Hex: log₁₆(num) (e.g., 16 for 64-bit numbers)

---

## Thread Safety

**Warning:** This implementation is **not thread-safe**.

Issues:
- Global or shared buffer states
- No mutex protection
- Race conditions possible in multi-threaded programs

For thread-safe operation:
- Use separate `_printf` calls per thread
- Implement mutex locking (not included)
- Consider thread-local storage for buffers

---

**[⬆ Back to Top](#api-reference---custom-printf)**