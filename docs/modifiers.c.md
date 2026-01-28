# modifiers.c

This file implements **field‐width** and **alignment** modifiers for a custom `printf`–style formatter. It provides three helper functions to insert leading or trailing spaces based on the parsed **width** and **minus (`-`)** flag. These routines keep conversion functions concise by centralizing space‐insertion logic.

---

## Overview

- Supplies **width modifiers** for formatted output.
- Inserts **leading** or **trailing** spaces to meet the field width.
- Works in concert with conversion routines (`_char`, `_string`, `_int`, etc.) to honor the `-` flag and width specifiers.

---

## Dependencies

- **`buffer_t`**: Holds the buffer state (`start`, `buffer`, `len`), defined in **main.h** .
- **`NEG_FLAG`**: Macro evaluating the `-` flag bit in the format flags, defined in **main.h** .
- **`_memcpy`**: Copies characters into the buffer (with auto‐flush at 1024 bytes), defined in **helpers.c** .

---

## 🛠️ Function Summary

| Function       | Purpose                                            | Common Callers                             |
| -------------- | -------------------------------------------------- | ------------------------------------------- |
| `print_width`  | Insert **leading** spaces when **no** `-` flag     | All conversion functions                    |
| `string_width` | Leading spaces for **strings** with precision rules| `_string`, `_r`, `_R`, `_S`                 |
| `neg_width`    | Append **trailing** spaces when **`-`** flag set   | After writing any conversion output         |

---

## Function Details

### 1. print_width

```c
unsigned int print_width(buffer_t *output,
                         unsigned int printed,
                         unsigned char flag,
                         int width);
```

**Description**  
Inserts **leading** spaces to satisfy `width` when the **minus** (`-`) flag is **not** set.

**Parameters**  
- `output`: Buffer state.  
- `printed`: Number of characters already written.  
- `flag`: Bitmask of parsed flags.  
- `width`: Desired field width.

**Returns**  
Number of spaces written.

**Behavior**  
- If `NEG_FLAG == 0`, calculates `width – printed`.  
- Loops, calling `_memcpy` to insert that many `' '` .

---

### 2. string_width

```c
unsigned int string_width(buffer_t *output,
                          unsigned char flag,
                          int width,
                          int precision,
                          int size);
```

**Description**  
Handles **leading** spacing for **string** conversions, honoring any **precision** (maximum characters to print).

**Parameters**  
- `output`: Buffer state.  
- `flag`: Parsed flags.  
- `width`: Field width.  
- `precision`: Max chars from string (`-1` if none).  
- `size`: Actual length of the input string.

**Returns**  
Number of leading spaces inserted.

**Behavior**  
- If `NEG_FLAG == 0`, computes `width – (precision == -1 ? size : precision)`.  
- Inserts spaces via `_memcpy` .

---

### 3. neg_width

```c
unsigned int neg_width(buffer_t *output,
                       unsigned int printed,
                       unsigned char flag,
                       int width);
```

**Description**  
Appends **trailing** spaces when the **minus** (`-`) flag is **set**, ensuring left‐justified output fills the field.

**Parameters**  
- `output`: Buffer state.  
- `printed`: Characters already output.  
- `flag`: Parsed flags.  
- `width`: Field width.

**Returns**  
Number of trailing spaces written.

**Behavior**  
- If `NEG_FLAG == 1`, calculates `width – printed`.  
- Writes spaces via `_memcpy` .

---

## Integration in Conversion Flow

Conversion functions typically follow this pattern:

```c
ret += print_width(output, ret, flag, width);
ret += /* write actual data: e.g. _memcpy, _sbase, _ubase */;
ret += neg_width(output, ret, flag, width);
```

This ensures that, regardless of data type, **width** and **alignment** are handled uniformly.

---

## Key Macros & Types

| Macro      | Value         | Description                         |
| ---------- | ------------- | ----------------------------------- |
| `NEG`      | 16            | Bitmask for `-` flag                |
| `NEG_FLAG` | `(flag>>4)&1` | True if `-` flag is present        | 
| `buffer_t` | struct        | Buffer pointer, start, and length   | 

---

## Conclusion 🎉

`modifiers.c` centralizes the **space‐insertion** logic for widths and left/right justification. By separating this concern from conversion routines, it promotes clarity and consistency across all formatted output.