# printf Library Overview  
This library provides a custom implementation of the C standard `printf` function, named `_printf`. It buffers output for efficient writes and supports most standard format specifiers (`%d`, `%x`, `%s`, etc.), plus extra conversions (`%b`, `%r`, `%R`, `%S`). The design is modular: each source file handles a specific responsibility, from buffer management to parsing flags and printing values.

## Header: main.h  
The central header defines macros, types and all function prototypes used across modules. It orchestrates flag handling, length modifiers, specifier dispatching, buffer management, and the public `_printf` API. 

### Flag Macros  
These bit-mask constants and helpers decode formatting flags in the format string.
| Name       | Value | Description                        |
|------------|:-----:|------------------------------------|
| `PLUS`     | 1     | Always prefix sign for numbers     |
| `SPACE`    | 2     | Prefix space for positive numbers  |
| `HASH`     | 4     | Alternate form (`0x`, leading 0)   |
| `ZERO`     | 8     | Pad numeric output with ‘0’        |
| `NEG`      | 16    | Left-justify within field width    |
| `PLUS_FLAG`| —     | `(flag & 1)`                        |
| `SPACE_FLAG`| —    | `((flag >> 1)&1)`                  |
| `HASH_FLAG`| —     | `((flag >> 2)&1)`                  |
| `ZERO_FLAG`| —     | `((flag >> 3)&1)`                  |
| `NEG_FLAG` | —     | `((flag >> 4)&1)`                  |

### Length Modifier Macros  
Support for `h` (short) and `l` (long).
- `SHORT` = 1  
- `LONG` = 2  

### Core Types  
| Type        | Purpose                                                 |
|-------------|---------------------------------------------------------|
| `buffer_t`  | Tracks a 1 kB output buffer, current pointer and length |
| `flag_t`    | Maps a flag character to its integer value              |
| `converter_t` | Associates a conversion specifier with its handler fn |

### Function Prototypes  
**Specifier functions** convert a `va_list` argument into text in the buffer:
```c
unsigned int _char(...);
unsigned int _string(...);
unsigned int _perc(...);
unsigned int _int(...);
unsigned int _bin(...);
unsigned int _dec(...);
unsigned int _oct(...);
unsigned int lower_hex(...);
unsigned int upper_hex(...);
unsigned int _S(...);
unsigned int _p(...);
unsigned int _r(...);
unsigned int _R(...);
```  
**Handler functions** parse format modifiers:
```c
unsigned char _flag(const char *fmt, char *i);
unsigned char _length(const char *mod, char *i);
int _width(va_list ap, const char *mod, char *i);
int _precision(va_list ap, const char *mod, char *i);
unsigned int (*_specifiers(const char *spec))(va_list, buffer_t *, unsigned char, int, int, unsigned char);
```  
**Width/precision modifiers** insert padding:
```c
unsigned int print_width(buffer_t *, unsigned int, unsigned char, int);
unsigned int string_width(buffer_t *, unsigned char, int, int, int);
unsigned int neg_width(buffer_t *, unsigned int, unsigned char, int);
```  
**Buffer helpers** manage the output buffer:
```c
buffer_t *init_buffer(void);
void free_buffer(buffer_t *);
unsigned int _memcpy(buffer_t *, const char *, unsigned int);
unsigned int _sbase(buffer_t *, long, char *, unsigned char, int, int);
unsigned int _ubase(buffer_t *, unsigned long, char *, unsigned char, int, int);
```  
**Public API**  
```c
int _printf(const char *format, ...);
``` 

---

## helpers.c  
This module implements buffer allocation and raw memory writes. It ensures buffered writes flush every 1024 bytes. 
- `_memcpy` – Copy `n` bytes into `output->buffer`, flushing when full.  
- `init_buffer` – Allocate and initialize a new `buffer_t`.  
- `free_buffer` – Release the buffer and struct.

```c
buffer_t *buf = init_buffer();
/* use _memcpy to append data */
free_buffer(buf);
```

---

## base.c  
Numeric conversion core: recursively builds signed and unsigned representations in any base. 
- `_sbase` – Convert a signed `long int` to digits in the given base.  
- `_ubase` – Convert an unsigned `long int` likewise, handling alternate‐form prefixes.

---

## converters.c ✨  
Handles the most common format specifiers. 
- `_char` (`%c`)  
- `_perc` (`%%`)  
- `_string` (`%s`)  
- `_int` and `_int` (`%d`, `%i`)  
- `_bin` (`%b`) – binary representation

Each function applies width/precision logic, calls `_memcpy`, then appends padding.

---

## converters2.c 🔢  
Unsigned and hex/octal conversions.  
- `_dec` (`%u`) – unsigned decimal  
- `_oct` (`%o`) – octal, with `#` prefix when requested  
- `lower_hex` (`%x`) – lowercase hex  
- `upper_hex` (`%X`) – uppercase hex  

---

## converters3.c 🔄  
Miscellaneous and advanced specifiers (prototypes in `main.h`). 
- `_S` – Print non‐printable characters as `\xHH`.  
- `_p` – Pointer address in hex, `nil` for null.  
- `_r` – Reverse string.  
- `_R` – ROT13‐encode the input string.

---

## handlers.c  
Parses format‐string directives in order: flags, width, precision, length and specifier lookup. 
1. `_flag` – Accumulate bit flags.  
2. `_width` – Read numeric or `*` width.  
3. `_precision` – Read precision after ‘.’.  
4. `_length` – Map `h`/`l`.  
5. `_specifiers` – Dispatch the correct conversion function.

---

## modifiers.c  
Implements field‐width and left‐justify logic:
- `print_width` – Pad before data if right‐justified.  
- `string_width` – Pad strings considering precision.  
- `neg_width` – Pad after data for left‐justified fields. 

---

# Usage Example  
```c
int main(void)
{
    _printf("Hello, %s! Num=%05d, Hex=%#x, Bin=%b\n", "World", 42, 255, 5);
    return 0;
}
```
This prints formatted output to **stdout** using an internal buffer, flushing automatically every 1024 characters.