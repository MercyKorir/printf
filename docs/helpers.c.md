# helpers.c 🔧

**helpers.c** provides core buffering utilities for a custom `_printf` implementation. It defines and manages a fixed-size buffer to accumulate output data, flushes it efficiently to standard output, and handles memory allocation and deallocation for the buffer.  

---

## buffer_t Structure

The `buffer_t` struct encapsulates the buffer state used throughout the printing machinery. It is declared in **main.h**:

```c
typedef struct buffer_s {
  char           *buffer;  // Current write position
  char           *start;   // Beginning of the buffer
  unsigned int    len;     // Number of bytes currently stored
} buffer_t;
```

- **buffer**: points to where the next byte will be written  
- **start**: marks the start of allocated memory  
- **len**: tracks how many bytes have been buffered so far 

---

## init_buffer 💡

```c
buffer_t *init_buffer(void);
```

Initializes a new `buffer_t` instance:

- Allocates memory for the `buffer_t` struct  
- Allocates a 1024-byte array for `buffer`  
- Sets `start = buffer`, `len = 0`  

Returns a pointer to the newly created buffer, or `NULL` on allocation failure .

---

## _memcpy 📋

```c
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
```

Copies `n` bytes from `src` into the buffer, flushing to **stdout** when full:

1. Loop over each of the `n` bytes:
   - Write `src[i]` into `*output->buffer`  
   - Increment `output->len`  
2. If `output->len` reaches **1024**:
   - Call `write(1, output->start, output->len)`  
   - Reset `output->buffer = output->start`, `output->len = 0`  
3. Otherwise, advance `output->buffer++`  

Returns the total bytes copied (`n`) .

---

## free_buffer 🗑️

```c
void free_buffer(buffer_t *output);
```

Frees all memory associated with a `buffer_t`:

- `free(output->start)`  
- `free(output)`  

Ensures no memory leaks occur after printing completes .

---

## Integration with Custom `_printf`

The buffering functions in **helpers.c** are leveraged by all specifier handlers to accumulate output before making a system call:

- **Character output** (e.g., `_char` in `converters.c`):
  ```c
  ret += _memcpy(output, &c, 1);
  ```  
- **String output** (e.g., `_string`):
  ```c
  ret += _memcpy(output, str, 1);
  ```  
- **Numeric conversions** use `_memcpy` indirectly via `_sbase` and `_ubase`.  

This design minimizes the number of `write` calls, batching up to 1024 bytes per system call and improving throughput .

---

## Function Summary

| Function       | Prototype                                           | Description                                            |
|----------------|-----------------------------------------------------|--------------------------------------------------------|
| **init_buffer**  | `buffer_t *init_buffer(void);`                      | Allocate and initialize a 1024-byte buffer             |
| **_memcpy**      | `unsigned int _memcpy(buffer_t *, const char *, unsigned int);` | Copy data into the buffer, flush on full               |
| **free_buffer**  | `void free_buffer(buffer_t *);`                     | Release buffer memory to avoid leaks                   |

---

## Dependencies & Relationships

- Relies on `<unistd.h>` for the `write` system call.  
- Defined in **main.h**, which also declares all specifier handlers and supports the `_printf` API.  
- Used by modules:  
  - `converters.c`  
  - `modifiers.c`  
  - `handlers.c`  
  - `base.c`  
  - `converters2.c` / `converters3.c`  

Together, these components form a modular, efficient printf-like library for formatted output.