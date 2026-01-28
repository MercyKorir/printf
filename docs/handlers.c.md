# handlers.c

This file implements the **parsing logic** for format specifiers in a custom `printf`-style function. It reads flags, width, precision, length modifiers, and selects the appropriate conversion function to format each argument into the output buffer .

## Dependencies

- **main.h**: Declares buffer, flag and converter types, plus macros for flags and length modifiers .
- **stdarg.h**: For `va_list` and accessing variadic arguments.
- **buffer_t**: Output buffer structure.
- **flag_t**, **converter_t**: Lookup tables for flags and specifiers.

---

## Flag Parsing: `_flag()` 🚩

**Purpose:** Reads one or more flag characters (`+`, `-`, space, `#`, `0`) from the format string, advances the index, and returns a bitmask of enabled flags.

```c
unsigned char _flag(const char *flag, char *i);
```

**Behavior:**
- Iterates through `flag[]` characters.
- Matches each against a lookup array of `flag_t` entries.
- Increments `*i` for each recognized flag.
- Combines all matched flag values via bitwise OR.
- Stops at first unrecognized character.

| Character | Macro    | Bitmask Value |
|-----------|----------|---------------|
| `+`       | `PLUS`   | 1             |
| `-`       | `NEG`    | 16            |
| (space)   | `SPACE`  | 2             |
| `#`       | `HASH`   | 4             |
| `0`       | `ZERO`   | 8             |

*Flag macros are defined in main.h* .

---

## Length Modifier: `_length()`

**Purpose:** Detects length modifiers `h` or `l`, advances the index, and returns a code indicating the modifier.

```c
unsigned char _length(const char *modifier, char *i);
```

| Modifier | Macro  | Description         |
|----------|--------|---------------------|
| `h`      | `SHORT`| Treat argument as `short`   |
| `l`      | `LONG` | Treat argument as `long`    |

- Returns `0` if no length modifier is present .
- Index `*i` is incremented when a modifier is consumed.

---

## Field Width: `_width()`

**Purpose:** Parses the **minimum field width** from the format string, handling both numeric and `*` values.

```c
int _width(va_list ap, const char *modifier, char *i);
```

**Behavior:**
- Reads digits (`0–9`) to build a numeric width.
- If `*` is encountered, fetches an `int` from `ap`:
  - If ≤ 0 ⇒ returns `0`.
  - Else returns that value.
- Stops when a non-digit, non-`*` character is reached.
- Advances `*i` for every character consumed .

---

## Precision: `_precision()`

**Purpose:** Parses the **precision** specifier (starts with `.`), supporting numeric and `*` forms.

```c
int _precision(va_list ap, const char *modifier, char *i);
```

**Rules:**
1. If the next character is not `.` ⇒ returns `-1` (no precision).
2. After `.`, reads digits or `*`:
   - `*` ⇒ `va_arg(ap, int)` if > 0; else returns `0`.
   - Digits ⇒ accumulates numeric value.
3. A bare `.` (followed by non-digit, non-`*`) ⇒ returns `0`.
4. Advances `*i` appropriately .

---

## Specifier Lookup: `_specifiers()` 🔍

**Purpose:** Maps a conversion specifier character to its formatting function.

```c
unsigned int (*_specifiers(const char *spec))
  (va_list, buffer_t *, unsigned char, int, int, unsigned char);
```

**Supported Specifiers & Functions:**

| Specifier | Function      | Description                    |
|-----------|---------------|--------------------------------|
| `c`       | `_char`       | Character                       |
| `s`       | `_string`     | String                          |
| `%`       | `_perc`       | Literal `%`                     |
| `d`, `i`  | `_int`        | Signed decimal integer          |
| `b`       | `_bin`        | Binary                          |
| `u`       | `_dec`        | Unsigned decimal                |
| `o`       | `_oct`        | Octal                           |
| `x`       | `lower_hex`   | Hexadecimal (lowercase)         |
| `X`       | `upper_hex`   | Hexadecimal (uppercase)         |
| `S`       | `_S`          | String with non-printables as `\x` |
| `p`       | `_p`          | Pointer address                 |
| `r`       | `_r`          | Reverse string                  |
| `R`       | `_R`          | ROT13 encoding                  |

Unrecognized specifiers yield `NULL`, signaling an error or literal output .

---

## Overall Flow

1. **Parse Flags** (`_flag`)  
2. **Parse Width** (`_width`)  
3. **Parse Precision** (`_precision`)  
4. **Parse Length** (`_length`)  
5. **Lookup Specifier** (`_specifiers`) → conversion function  
6. **Invoke** conversion, writing into **buffer_t**  

```c
/* Simplified flow */
while (*format) {
  if (*format == '%') {
    format++;
    flags     = _flag(format, &i);
    width     = _width(ap, format + i, &i);
    precision = _precision(ap, format + i, &i);
    length    = _length(format + i, &i);
    func      = _specifiers(format + i);
    printed  += func(ap, buffer, flags, width, precision, length);
    format   += i + 1;
  } else {
    printed += _memcpy(buffer, format++, 1);
  }
}
```

---

**handlers.c** is a **core component** in this `printf` implementation, responsible for dissecting format directives and delegating to type-specific converters. It ensures that flags, widths, precisions, and length modifiers are correctly interpreted before formatting each argument.