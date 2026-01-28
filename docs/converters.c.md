# converters.c

This file implements the **core conversion functions** for a custom `_printf`-style routine. Each function handles one format specifier—reading the appropriate argument from the `va_list`, applying flags, width, precision, and length modifiers, and writing formatted output into the shared `buffer_t` structure. These converters rely on helper routines for padding and base conversion .

```c
#include "main.h"

unsigned int _char(va_list ap, buffer_t *output,
                   unsigned char flag, int width,
                   int precision, unsigned char len);
unsigned int _perc(va_list ap, buffer_t *output,
                   unsigned char flag, int width,
                   int precision, unsigned char len);
unsigned int _string(va_list ap, buffer_t *output,
                     unsigned char flag, int width,
                     int precision, unsigned char len);
unsigned int _int(va_list ap, buffer_t *output,
                  unsigned char flag, int width,
                  int precision, unsigned char len);
unsigned int _bin(va_list ap, buffer_t *output,
                  unsigned char flag, int width,
                  int precision, unsigned char len);
```
*Prototypes for all converters* .

---

### Conversion Specifiers Table

| Specifier | Function | Description                       |
|-----------|----------|-----------------------------------|
| `c`       | `_char`  | Prints a single character 🎴       |
| `%`       | `_perc`  | Prints a literal percent sign 💯   |
| `s`       | `_string`| Prints a null-terminated string 📝 |
| `d`, `i`  | `_int`   | Prints signed decimal integers 🔢  |
| `b`       | `_bin`   | Prints unsigned binary (base 2)    |

*Mapping defined in* `handlers.c` .

---

## `_char` 🎴

Converts the next argument to an unsigned character and writes it, with optional padding.

```c
unsigned int _char(va_list ap, buffer_t *output,
                   unsigned char flag, int width,
                   int precision, unsigned char len)
{
    char c = va_arg(ap, int);
    unsigned int ret = 0;

    (void)precision;  /* ignored */
    (void)len;        /* ignored */

    ret += print_width(output, ret, flag, width);
    ret += _memcpy(output, &c, 1);
    ret += neg_width(output, ret, flag, width);

    return ret;
}
```

- Retrieves the character via `va_arg(ap, int)`.
- Applies **left padding** (`print_width`) and **right padding** (`neg_width`).
- Writes the character byte with `_memcpy` .

---

## `_perc` 💯

Handles the `%%` sequence by outputting a single `%` character.

```c
unsigned int _perc(va_list ap, buffer_t *output,
                   unsigned char flag, int width,
                   int precision, unsigned char len)
{
    char percent = '%';
    unsigned int ret = 0;

    (void)ap;        /* no arg consumed */
    (void)precision; /* ignored */
    (void)len;       /* ignored */

    ret += print_width(output, ret, flag, width);
    ret += _memcpy(output, &percent, 1);
    ret += neg_width(output, ret, flag, width);

    return ret;
}
```

- Always prints `%` regardless of arguments.
- Observes field width for alignment .

---

## `_string` 📝

Formats a C-string with optional precision (max chars) and width.

```c
unsigned int _string(va_list ap, buffer_t *output,
                     unsigned char flag, int width,
                     int precision, unsigned char len)
{
    char *str = va_arg(ap, char *);
    char *null = "(null)";
    int size = 0;
    unsigned int ret = 0;

    (void)flag; /* flags handled in padding */
    (void)len;  /* no length modifiers */

    if (str == NULL)
        return _memcpy(output, null, 6);

    while (str[size])
        size++;

    ret += string_width(output, flag, width, precision, size);

    /* If precision < 0, print entire string */
    precision = (precision == -1) ? size : precision;
    while (*str && precision-- > 0)
    {
        ret += _memcpy(output, str++, 1);
    }

    ret += neg_width(output, ret, flag, width);
    return ret;
}
```

- Prints `"(null)"` if the string pointer is `NULL`.
- Uses `string_width` for **left padding** and `neg_width` for **trailing spaces**.
- Honors `precision` as maximum characters to output .

---

## `_int` 🔢

Converts a signed integer to decimal, handling flags (`+`, space, `0`, `-`), width, and precision.

```c
unsigned int _int(va_list ap, buffer_t *output,
                  unsigned char flag, int width,
                  int precision, unsigned char len)
{
    long int d;
    unsigned int ret = 0, count = 0;
    char pad, space = ' ', neg = '-', plus = '+';
    long int copy;

    /* Select type based on length modifier */
    if (len == LONG)
        d = va_arg(ap, long int);
    else
        d = va_arg(ap, int);
    if (len == SHORT)
        d = (short)d;

    /* Space flag prints a leading space for positives */
    if (SPACE_FLAG && d >= 0)
        ret += _memcpy(output, &space, 1);

    /* Calculate digit count for padding */
    if (precision <= 0 && !NEG_FLAG)
    {
        if (d == LONG_MIN)
            count += 19;
        else
        {
            for (copy = (d < 0) ? -d : d; copy; copy /= 10)
                count++;
            if (d == 0)                count++;
            if (d < 0)                 count++;
            if (PLUS_FLAG && d >= 0)   count++;
            if (SPACE_FLAG && d >= 0)  count++;
        }

        /* Leading sign before zero padding */
        if (ZERO_FLAG && PLUS_FLAG && d >= 0)
            ret += _memcpy(output, &plus, 1);
        if (ZERO_FLAG && d < 0)
            ret += _memcpy(output, &neg, 1);

        pad = (ZERO_FLAG) ? '0' : ' ';
        for (width -= count; width > 0; width--)
            ret += _memcpy(output, &pad, 1);
    }

    /* Non-zero flags after zero padding */
    if (!ZERO_FLAG && d < 0)
        ret += _memcpy(output, &neg, 1);
    if (!ZERO_FLAG && PLUS_FLAG && d >= 0)
        ret += _memcpy(output, &plus, 1);

    /* Write the number itself */
    if (!(d == 0 && precision == 0))
        ret += _sbase(output, d, "0123456789", flag, 0, precision);

    ret += neg_width(output, ret, flag, width);
    return ret;
}
```

- Handles **sign**, **zero-padding**, **space**, and **plus** flags.
- Counts characters to compute padding.
- Uses `_sbase` to perform recursive decimal conversion.
- Applies **trailing spaces** if the `-` (NEG) flag is set .

---

## `_bin` 📊

Prints an unsigned integer in binary (base 2) using the generic `_ubase` routine.

```c
unsigned int _bin(va_list ap, buffer_t *output,
                  unsigned char flag, int width,
                  int precision, unsigned char len)
{
    unsigned int num = va_arg(ap, unsigned int);
    (void)len; /* no length modifiers */

    return _ubase(output, num, "01", flag, width, precision);
}
```

- Delegates to `_ubase`, which handles padding and base-conversion logic.
- Supports `#` flag via the `flag` bitmask, if implemented in `_ubase` .

---

## Dependencies & Helpers

- **buffer_t**: Holds a 1024-byte buffer, current write pointer, and length counter .
- **_memcpy** (helpers.c): Writes raw bytes into `buffer_t`, auto-flushing on full buffer.
- **print_width**, **string_width**, **neg_width** (modifiers.c): Manage leading/trailing padding based on flags, width, and precision.
- **_sbase**, **_ubase** (base.c): Recursive routines converting numbers to arbitrary bases.

---

> **Design Note:**  
> New format specifiers can be added by implementing a converter function with the same prototype, then registering it in the `converter_t` array within the `_specifiers` handler (see `handlers.c`) . This modular approach cleanly separates parsing from conversion logic.