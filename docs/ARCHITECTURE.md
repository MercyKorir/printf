# Architecture Overview - Custom Printf

## Table of Contents

- [System Overview](#system-overview)
- [Design Philosophy](#design-philosophy)
- [Module Architecture](#module-architecture)
- [Data Flow](#data-flow)
- [Component Interaction](#component-interaction)
- [Buffer Management](#buffer-management)
- [Parsing Strategy](#parsing-strategy)
- [Conversion Pipeline](#conversion-pipeline)
- [Memory Management](#memory-management)
- [Performance Optimization](#performance-optimization)
- [Extensibility](#extensibility)

---

## System Overview

This custom `printf` implementation is a **modular**, **buffered I/O system** that converts variadic function arguments into formatted text output. The design emphasizes:

- **Separation of concerns**: Each module has a distinct responsibility
- **Efficient buffering**: Minimizes system calls with 1024-byte buffer
- **Recursive algorithms**: Base conversion uses elegant recursion
- **Extensible design**: Easy to add new format specifiers

### High-Level Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                      User Application                       │
└─────────────────────────┬───────────────────────────────────┘
                          │ _printf(format, ...)
                          ↓
┌─────────────────────────────────────────────────────────────┐
│                    Core: _printf.c                          │
│  • Validates input                                          │
│  • Initializes buffer                                       │
│  • Orchestrates parsing and conversion                      │
└─────────────────────────┬───────────────────────────────────┘
                          │
                          ↓
            ┌─────────────┴──────────────┐
            │                            │
            ↓                            ↓
┌───────────────────────┐    ┌──────────────────────┐
│  Parsing: handlers.c  │    │  Buffer: helpers.c   │
│  • Parse flags        │    │  • Allocate buffer   │
│  • Parse width        │    │  • Write bytes       │
│  • Parse precision    │    │  • Auto-flush        │
│  • Parse length       │    │  • Free buffer       │
│  • Select converter   │    └──────────────────────┘
└───────────┬───────────┘
            │
            ↓
┌───────────────────────────────────────────────────────┐
│              Conversion Layer                         │
│  ┌──────────────┐  ┌──────────────┐  ┌─────────────┐  │
│  │converters.c  │  │converters2.c │  │converters3.c│  │
│  │ Basic specs  │  │ Numeric specs│  │ Custom specs│  │
│  │ %c %s %d %i  │  │ %u %o %x %X  │  │ %b %r %R %S │  │
│  └──────┬───────┘  └──────┬───────┘  └──────┬──────┘  │
│         └─────────────────┴─────────────────┘         │
└────────────────────────┬──────────────────────────────┘
                         │
                         ↓
┌────────────────────────────────────────────────────────┐
│              Support Modules                           │
│  ┌───────────────┐  ┌──────────────┐                   │
│  │ modifiers.c   │  │   base.c     │                   │
│  │ Width/padding │  │ Base convert │                   │
│  └───────────────┘  └──────────────┘                   │
└────────────────────────────────────────────────────────┘
                         │
                         ↓
┌────────────────────────────────────────────────────────┐
│                System Call Layer                       │
│             write(1, buffer, length)                   │
│                  (STDOUT)                              │
└────────────────────────────────────────────────────────┘
```

---

## Design Philosophy

### Core Principles

1. **Modularity**
   - Each module has a single, well-defined responsibility
   - Modules can be tested and maintained independently
   - New features can be added without modifying existing code

2. **Efficiency**
   - Buffered output reduces system call overhead
   - Recursive algorithms are elegant and maintainable
   - Direct memory operations avoid unnecessary copying

3. **Correctness**
   - Comprehensive error checking
   - Memory leak prevention through paired allocation/deallocation
   - Consistent handling of edge cases (NULL, empty strings, etc.)

4. **Extensibility**
   - New format specifiers require minimal changes
   - Flag system uses bitmasks for easy addition
   - Converter dispatch table simplifies routing

---

## Module Architecture

### 1. Core Module (_printf.c)

**Responsibility:** Entry point and orchestration

**Key Functions:**
- `_printf()` - Main API function
- `run()` - Format string iteration and dispatch
- `clean()` - Cleanup and final flush

**Design Pattern:** Facade pattern - provides simple interface to complex subsystem

```c
int _printf(const char *format, ...)
{
    buffer_t *output = init_buffer();
    va_list ap;
    
    va_start(ap, format);
    int ret = run(format, ap, output);
    
    return ret; /* clean() called inside run() */
}
```

---

### 2. Buffer Management (helpers.c)

**Responsibility:** Memory allocation and I/O buffering

**Key Functions:**
- `init_buffer()` - Allocate 1024-byte buffer
- `_memcpy()` - Write to buffer with auto-flush
- `free_buffer()` - Release buffer memory

**Design Pattern:** Resource Acquisition Is Initialization (RAII-like in C)

**Buffer States:**

```
State 1: Empty Buffer
┌────────────────────────────────────────────┐
│ [empty space - 1024 bytes]                 │
└────────────────────────────────────────────┘
 ↑
start, buffer (len = 0)

State 2: Partially Filled
┌────────────────────────────────────────────┐
│ [data - 500 bytes] [empty - 524 bytes]     │
└────────────────────────────────────────────┘
 ↑                   ↑
start              buffer (len = 500)

State 3: Full (triggers flush)
┌────────────────────────────────────────────┐
│ [data - 1024 bytes]                        │
└────────────────────────────────────────────┘
 ↑
start, buffer (len = 1024)
→ write(1, start, 1024)
→ buffer = start, len = 0
```

---

### 3. Format Parsing (handlers.c)

**Responsibility:** Parse format string and extract modifiers

**Key Functions:**
- `_flag()` - Parse flag characters
- `_width()` - Parse field width
- `_precision()` - Parse precision
- `_length()` - Parse length modifiers
- `_specifiers()` - Map specifier to handler

**Design Pattern:** Chain of Responsibility + Strategy

**Parsing Flow:**

```
Input: "%+010.5ld"
       ↓
┌──────────────┐
│   _flag()    │ → flags = PLUS | ZERO
└──────┬───────┘
       ↓
┌──────────────┐
│   _width()   │ → width = 10
└──────┬───────┘
       ↓
┌──────────────┐
│ _precision() │ → precision = 5
└──────┬───────┘
       ↓
┌──────────────┐
│  _length()   │ → len = LONG
└──────┬───────┘
       ↓
┌──────────────┐
│_specifiers() │ → func = _int
└──────────────┘
```

---

### 4. Width/Padding (modifiers.c)

**Responsibility:** Handle field width and alignment

**Key Functions:**
- `print_width()` - Leading padding (right-justify)
- `string_width()` - String-specific padding
- `neg_width()` - Trailing padding (left-justify)

**Design Pattern:** Template Method

**Padding Logic:**

```
Right-justify (default):
┌────────────────────────────────┐
│ [spaces] [content]             │
└────────────────────────────────┘
  print_width()

Left-justify (- flag):
┌────────────────────────────────┐
│ [content] [spaces]             │
└────────────────────────────────┘
             neg_width()
```

---

### 5. Base Conversion (base.c)

**Responsibility:** Convert numbers to different bases

**Key Functions:**
- `_sbase()` - Signed integer conversion
- `_ubase()` - Unsigned integer conversion

**Algorithm:** Recursive divide-and-conquer

**Example: 42 in decimal (base 10)**

```
_sbase(42, "0123456789")
    → _sbase(4, "0123456789")  /* 42 / 10 = 4 */
        → _sbase(0, ...)       /* 4 / 10 = 0 (stop) */
        → write('4')           /* 4 % 10 = 4 */
    → write('2')               /* 42 % 10 = 2 */
Output: "42"
```

---

### 6. Converter Modules (converters*.c)

**Responsibility:** Implement format specifiers

**Organization:**
- `converters.c` - Basic types (%c, %s, %d, %i, %b)
- `converters2.c` - Numeric types (%u, %o, %x, %X)
- `converters3.c` - Custom types (%r, %R, %S, %p)

**Design Pattern:** Strategy pattern

**Converter Signature:**
```c
unsigned int converter(
    va_list ap,           /* Arguments */
    buffer_t *output,     /* Output buffer */
    unsigned char flag,   /* Flags */
    int width,            /* Field width */
    int precision,        /* Precision */
    unsigned char len     /* Length modifier */
);
```

---

## Data Flow

### Complete Execution Flow

```
1. User calls _printf("Value: %+05d", 42)
   ↓
2. _printf() allocates buffer via init_buffer()
   ↓
3. run() iterates through format string
   ↓
4. Encounters '%', calls parsing functions:
   _flag()      → flags = PLUS | ZERO
   _width()     → width = 5
   _precision() → precision = -1
   _length()    → len = 0
   _specifiers()→ func = _int
   ↓
5. Calls _int(ap, buffer, PLUS|ZERO, 5, -1, 0)
   ↓
6. _int() processes:
   - Extracts 42 from va_list
   - Calculates padding needs
   - Writes '+' for PLUS flag
   - Writes leading zeros (ZERO flag)
   - Calls _sbase(42, "0123456789")
   ↓
7. _sbase() recursively writes "42"
   ↓
8. Output: "+0042"
   ↓
9. clean() flushes buffer and frees memory
   ↓
10. Returns 5 (characters written)
```

---

## Component Interaction

### Interaction Diagram

```
┌──────────┐
│ _printf  │
│  Entry   │
└────┬─────┘
     │ init_buffer()
     ↓
┌──────────┐      ┌──────────┐
│  Buffer  │←────→│   run    │
│  Module  │      │  Loop    │
└──────────┘      └────┬─────┘
                       │
                       ↓
                  ┌─────────┐
                  │Handlers │
                  │  Parse  │
                  └────┬────┘
                       │
         ┌─────────────┼─────────────┐
         ↓             ↓             ↓
    ┌────────┐   ┌─────────┐   ┌─────────┐
    │Convert │   │ Modify  │   │  Base   │
    │  ers   │   │  ers    │   │ Convert │
    └────┬───┘   └────┬────┘   └────┬────┘
         │            │             │
         └────────────┼─────────────┘
                      ↓
                ┌──────────┐
                │  _memcpy │
                │  Write   │
                └──────────┘
                      ↓
                ┌──────────┐
                │  Flush   │
                │ (write)  │
                └──────────┘
```

---

## Buffer Management

### Buffer Lifecycle

```
Phase 1: Allocation
┌─────────────────┐
│ init_buffer()   │ → malloc(buffer_t)
└────────┬────────┘   malloc(1024 bytes)
         │
         ↓
Phase 2: Writing
┌─────────────────┐
│   _memcpy()     │ → Copy bytes to buffer
└────────┬────────┘   Increment length
         │           If length == 1024:
         │              write(1, ...)
         │              Reset length
         ↓
Phase 3: Flush
┌─────────────────┐
│    clean()      │ → write(1, ...) remaining bytes
└────────┬────────┘   
         │
         ↓
Phase 4: Cleanup
┌─────────────────┐
│ free_buffer()   │ → free(buffer memory)
└─────────────────┘   free(struct)
```

### Flush Triggers

1. **Automatic**: Buffer reaches 1024 bytes
2. **Manual**: `clean()` function at end of `_printf()`

### Performance Impact

```
Without buffering:
printf("Hello World") → 11 write() calls

With buffering:
printf("Hello World") → 1 write() call (at end)

Improvement: ~91% reduction in system calls
```

---

## Parsing Strategy

### State Machine Approach

The format string parser operates as a state machine:

```
States:
- LITERAL: Regular characters
- PERCENT: Just saw '%'
- FLAGS: Parsing flags (+, -, space, #, 0)
- WIDTH: Parsing width (digits or *)
- PRECISION: Parsing precision (. followed by digits or *)
- LENGTH: Parsing length modifier (h, l)
- SPECIFIER: Processing conversion specifier

Transitions:
LITERAL → PERCENT (on '%')
PERCENT → FLAGS (on flag character)
FLAGS → WIDTH (on digit or end of flags)
WIDTH → PRECISION (on '.')
PRECISION → LENGTH (on 'h' or 'l')
LENGTH → SPECIFIER (on specifier character)
SPECIFIER → LITERAL (continue scanning)
```

---

## Conversion Pipeline

### Standard Conversion Flow

Every converter follows this pattern:

```c
unsigned int converter(...)
{
    unsigned int ret = 0;
    
    /* 1. Extract argument */
    type value = va_arg(ap, type);
    
    /* 2. Handle special cases */
    if (value == NULL) /* for pointers/strings */
        return _memcpy(output, null_string, length);
    
    /* 3. Leading padding */
    ret += print_width(output, ret, flag, width);
    
    /* 4. Write content */
    ret += /* write actual value */;
    
    /* 5. Trailing padding */
    ret += neg_width(output, ret, flag, width);
    
    return ret;
}
```

---

## Memory Management

### Allocation Strategy

**Stack Allocations:**
- Local variables in functions
- va_list structures

**Heap Allocations:**
- `buffer_t` structure (in `init_buffer`)
- 1024-byte buffer array (in `init_buffer`)

**Memory Guarantees:**
- Every `init_buffer()` is paired with `free_buffer()`
- No memory leaks in normal execution
- Failed allocations return early with error code

### Memory Safety

```c
/* Proper cleanup on error */
buffer_t *output = init_buffer();
if (output == NULL)
    return -1;  /* No memory leak */

/* ... use buffer ... */

free_buffer(output);  /* Always reached */
```

---

## Performance Optimization

### 1. Buffered I/O

**Impact:** Reduces system call overhead by ~91%

**Technique:** Accumulate up to 1024 bytes before calling `write()`

### 2. Efficient Recursion

**Impact:** Clean, maintainable code with minimal stack usage

**Stack depth:** O(log_base(n)) for number n in base b

### 3. Direct Memory Operations

**Impact:** No unnecessary string concatenation or temporary buffers

**Technique:** Write directly to output buffer with `_memcpy()`

### 4. Bitwise Flag Operations

**Impact:** Fast flag checking and manipulation

```c
/* Fast: Single bitwise AND */
if (flag & PLUS)  /* O(1) */

/* vs. Slow: Multiple comparisons */
if (flag_plus == 1 && ...)  /* O(n) */
```

---

## Extensibility

### Adding a New Format Specifier

**Step 1:** Implement converter function

```c
/* In appropriate converters*.c file */
unsigned int _new_spec(va_list ap, buffer_t *output,
                       unsigned char flag, int width,
                       int precision, unsigned char len)
{
    /* Implementation */
}
```

**Step 2:** Add prototype to main.h

```c
unsigned int _new_spec(va_list ap, buffer_t *output,
                      unsigned char flag, int width,
                      int precision, unsigned char len);
```

**Step 3:** Register in converter table

```c
/* In handlers.c, _specifiers() function */
converter_t conv[] = {
    /* ... existing entries ... */
    {'N', _new_spec},  /* New specifier */
    {0, NULL}
};
```

### Adding a New Flag

**Step 1:** Define flag constant

```c
/* In main.h */
#define NEWFLAG 32  /* Next available bit */
#define NEWFLAG_CHECK ((flag >> 5) & 1)
```

**Step 2:** Register in flag table

```c
/* In handlers.c, _flag() function */
flag_t flags[] = {
    /* ... existing entries ... */
    {'N', NEWFLAG},  /* New flag character */
    {0, 0}
};
```

**Step 3:** Check flag in converters

```c
if (NEWFLAG_CHECK)
    /* Handle new flag */
```

---

## Design Patterns Used

| Pattern                 | Module        | Purpose                     |
|-------------------------|---------------|-----------------------------|
| Facade                  | _printf.c     | Simplify complex subsystem  |
| Strategy                | converters*.c | Interchangeable algorithms  |
| Chain of Responsibility | handlers.c    | Sequential parsing          |
| Template Method         | modifiers.c   | Consistent padding workflow |
| RAII-like               | helpers.c     | Resource management         |

---

## Testing Strategy

### Unit Testing Approach

1. **Module-level tests** - Test each module in isolation
2. **Integration tests** - Test module interactions
3. **End-to-end tests** - Test complete format strings
4. **Edge case tests** - NULL, empty strings, limits
5. **Memory tests** - Valgrind for leak detection

### Test Coverage

```
Module           Coverage Goal
---------------------------------
_printf.c        100% (simple orchestration)
helpers.c        100% (critical for memory)
handlers.c       100% (all parsing paths)
modifiers.c      100% (all padding cases)
base.c           95%  (all bases + edge cases)
converters*.c    90%  (all specifiers + flags)
```

---

## Future Enhancements

### Potential Improvements

1. **Thread Safety**
   - Add mutex locks around buffer operations
   - Thread-local storage for buffers

2. **Performance**
   - Compile-time format string validation
   - SIMD optimizations for bulk writes

3. **Features**
   - Floating point support (%f, %e, %g)
   - Wide character support (%ls, %lc)
   - Dynamic field width from arguments

4. **Robustness**
   - More comprehensive error codes
   - Stack overflow protection for recursion
   - Buffer size configuration

---

**[⬆ Back to Top](#architecture-overview---custom-printf)**