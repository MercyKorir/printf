# converters3.c Overview

`converters3.c` extends the custom `printf`-like engine by implementing **four special format specifiers** that handle strings and pointers in unique ways. It provides:

- 🔄 Reverse-string output (`%r`)
- 🔐 ROT13-encoded output (`%R`)
- 📍 Pointer address formatting (`%p`)
- 🔣 Non-printable character escaping (`%S`)

These functions integrate with the central formatting loop, writing into a `buffer_t` and respecting width, precision, and flag modifiers .

---

## Dependencies

- **main.h** for core types and macros:
  - `buffer_t` struct for output buffering 
  - Flag macros (`PLUS_FLAG`, `NEG_FLAG`, etc.)  
- **helpers.c** for raw memory writes:
  - `_memcpy` to append bytes into `buffer_t` 
- **modifiers.c** for width handling:
  - `string_width` and `neg_width` to pad before/after content 
- **base.c** for numeric base conversion:
  - `_ubase` to render numbers in hexadecimal 

---

## Specifier Summary

| Specifier | Function | Description                                |
|:---------:|:---------|:-------------------------------------------|
| %r        | `_r`     | Print string in **reverse** 🔄             |
| %R        | `_R`     | Print string in **ROT13** 🔐               |
| %p        | `_p`     | Print **pointer** address in hex 📍         |
| %S        | `_S`     | Print string, **escape** non-printables 🔣  |

---

## Detailed Function Reference

### _r — Reverse String 🔄

Prints the given string **backwards**, honoring width/precision and flags.

```c
unsigned int _r(va_list ap,
                buffer_t *output,
                unsigned char flag,
                int width,
                int precision,
                unsigned char len);
```

- **NULL input** → prints `"(null)"` (6 bytes)  
- **Compute length** `size` of `str`  
- **Left-pad** using `string_width(output, flag, width, precision, size)`  
- **Copy** up to `precision` characters in reverse order via `_memcpy`  
- **Right-pad** if `-` flag set via `neg_width`  
- **Returns** total bytes written 

---

### _R — ROT13 Encoding 🔐

Applies the ROT13 cipher to **alphabetic** characters; others pass through.

```c
unsigned int _R(va_list ap,
                buffer_t *output,
                unsigned char flag,
                int width,
                int precision,
                unsigned char len);
```

1. Retrieve `str`; **NULL** → `"(null)"`.  
2. Determine `size`, then **pad left**.  
3. For each char up to `precision`:
   - Lookup in `"a…zA…Z"` map → corresponding `"n…mN…M"`  
   - If no match, output char unchanged via `_memcpy`.  
4. **Pad right** if needed.  
5. **Returns** bytes written 

---

### _p — Pointer Address 📍

Formats a pointer value as `0x...` in **lowercase hexadecimal**.

```c
unsigned int _p(va_list ap,
                buffer_t *output,
                unsigned char flag,
                int width,
                int precision,
                unsigned char len);
```

- Fetches an `unsigned long int addr`.  
- If `addr == 0`, prints `"(nil)"` (5 bytes).  
- Sets a custom “lead” flag bit (`flag |= 32`).  
- Calls `_ubase(output, addr, "0123456789abcdef", flag, width, precision)` to emit `0x` prefix and hex digits.  
- Applies `neg_width` for trailing padding.  
- **Returns** bytes written 

---

### _S — Escape Non-Printables 🔣

Prints a string but **escapes** any char outside the printable ASCII range with `\xHH`.

```c
unsigned int _S(va_list ap,
                buffer_t *output,
                unsigned char flag,
                int width,
                int precision,
                unsigned char len);
```

- **NULL** → `"(null)"`.  
- Compute `size`, then **pad left**.  
- Iterate each char up to `precision`:
  - If `< 32` or `>= 127`:
    - Output `"\x"` via `_memcpy`
    - If byte `< 0x10`, emit a leading `0`  
    - Call `_ubase(..., "0123456789ABCDEF", flag, 0, 0)` to print two uppercase hex digits  
  - Else, copy the character as-is.  
- **Pad right** if `-` flag is set.  
- **Returns** bytes written 

---

## Integration with Specifier Handler

All four functions are registered in the converter table inside **handlers.c**, mapping their specifier characters to these implementations:

```c
converter_t conv[] = {
  /* … */
  {'S', _S},
  {'p', _p},
  {'r', _r},
  {'R', _R},
  {0, NULL}
};
```

This ensures `%r`, `%R`, `%p`, and `%S` invoke the correct converter at runtime .

---

```card
{
  "title": "Custom Specifiers",
  "content": "Use %r, %R, %p, and %S for reverse, ROT13, pointer, and escape-string formatting."
}
```