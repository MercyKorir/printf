# Printf Project - Complete Setup Guide for WSL Ubuntu

This guide provides step-by-step instructions to compile and run your custom printf implementation on WSL Ubuntu.

## Project Files

Your project contains these source files:
- `main.h` - Header with all declarations
- `_printf.c` - Main printf implementation
- `helpers.c` - Buffer management
- `handlers.c` - Format string parsing
- `modifiers.c` - Width and padding
- `base.c` - Base conversion functions
- `converters.c` - Basic converters (%c, %s, %d, %i, %b)
- `converters2.c` - Numeric converters (%u, %o, %x, %X)
- `converters3.c` - Special converters (%S, %p, %r, %R)

## Quick Start (3 Steps)

### Step 1: Create a Test File

```bash
nano main.c
```

Copy this content:
```c
#include "main.h"

int main(void)
{
    int len;

    /* Basic tests */
    _printf("=== Basic Tests ===\n");
    len = _printf("Hello, World!\n");
    _printf("Length: %d\n\n", len);

    /* Character and string tests */
    _printf("=== Character & String Tests ===\n");
    _printf("Character: %c\n", 'A');
    _printf("String: %s\n", "Hello, WSL Ubuntu!");
    _printf("Percent: %%\n\n");

    /* Integer tests */
    _printf("=== Integer Tests ===\n");
    _printf("Integer: %d\n", 42);
    _printf("Negative: %i\n", -42);
    _printf("Unsigned: %u\n", 123456);
    _printf("Zero: %d\n\n", 0);

    /* Binary, hex, and octal tests */
    _printf("=== Binary, Hex & Octal Tests ===\n");
    _printf("Binary of 42: %b\n", 42);
    _printf("Hex (lower) of 255: %x\n", 255);
    _printf("Hex (upper) of 255: %X\n", 255);
    _printf("Octal of 64: %o\n\n", 64);

    /* Pointer test */
    _printf("=== Pointer Test ===\n");
    int num = 10;
    _printf("Pointer address: %p\n\n", (void *)&num);

    /* Flag tests */
    _printf("=== Flag Tests ===\n");
    _printf("With plus flag: %+d\n", 42);
    _printf("With space flag: % d\n", 42);
    _printf("With hash flag (hex): %#x\n", 255);
    _printf("With hash flag (octal): %#o\n", 64);
    _printf("With zero padding: %05d\n\n", 42);

    /* Width and precision tests */
    _printf("=== Width & Precision Tests ===\n");
    _printf("Width 10, right-aligned: |%10d|\n", 42);
    _printf("Width 10, left-aligned: |%-10d|\n", 42);
    _printf("Precision 5: %.5d\n", 42);
    _printf("Width 10, precision 5: |%10.5d|\n\n", 42);

    /* String width tests */
    _printf("=== String Width Tests ===\n");
    _printf("Width 20: |%20s|\n", "Hello");
    _printf("Left-aligned: |%-20s|\n", "Hello");
    _printf("Precision 3: %.3s\n\n", "Hello");

    /* Special converters */
    _printf("=== Special Converters ===\n");
    _printf("Reversed string: %r\n", "Hello");
    _printf("ROT13 encoded: %R\n\n", "Hello");

    /* Edge cases */
    _printf("=== Edge Cases ===\n");
    _printf("NULL string: %s\n", NULL);
    _printf("NULL pointer: %p\n", NULL);
    _printf("Large number: %d\n", 2147483647);
    _printf("Negative large: %d\n", -2147483648);

    return (0);
}
```

### Step 2: Compile the Project

**Option A: Using the provided Makefile**
```bash
make
```

**Option B: Manual compilation (if no Makefile)**
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \
    main.c _printf.c helpers.c handlers.c modifiers.c \
    base.c converters.c converters2.c converters3.c \
    -o printf_test
```

**Option C: Compile with debugging symbols**
```bash
gcc -Wall -Wextra -pedantic -std=gnu89 -g \
    main.c _printf.c helpers.c handlers.c modifiers.c \
    base.c converters.c converters2.c converters3.c \
    -o printf_test
```

### Step 3: Run the Program

```bash
./printf_test
```

## Detailed Compilation Options

### Understanding the Compiler Flags

| Flag | Purpose |
|------|---------|
| `-Wall` | Enable all common warning messages |
| `-Werror` | Treat all warnings as errors |
| `-Wextra` | Enable extra warning flags not covered by -Wall |
| `-pedantic` | Issue warnings for code that doesn't follow ISO C standard |
| `-std=gnu89` | Use GNU89 C standard (C89 with GNU extensions) |
| `-g` | Include debugging information for use with gdb |
| `-o printf_test` | Name the output executable "printf_test" |

### Compilation Troubleshooting

**Issue 1: Undefined reference errors**
```
Solution: Make sure all .c files are included in the compilation command
```

**Issue 2: Implicit function declaration warnings**
```
Solution: Ensure main.h is included in all source files
```

**Issue 3: Permission denied when running**
```bash
chmod +x printf_test
./printf_test
```

## Alternative Compilation Methods

### Method 1: Compile Object Files Separately

This is useful for large projects:

```bash
# Compile each source file to object file
gcc -Wall -Wextra -pedantic -std=gnu89 -c _printf.c -o _printf.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c helpers.c -o helpers.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c handlers.c -o handlers.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c modifiers.c -o modifiers.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c base.c -o base.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters.c -o converters.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters2.c -o converters2.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters3.c -o converters3.o
gcc -Wall -Wextra -pedantic -std=gnu89 -c main.c -o main.o

# Link all object files
gcc main.o _printf.o helpers.o handlers.o modifiers.o base.o \
    converters.o converters2.o converters3.o -o printf_test

# Clean up object files
rm *.o
```

### Method 2: Create a Static Library

```bash
# Compile all source files to object files (except main.c)
gcc -Wall -Wextra -pedantic -std=gnu89 -c _printf.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c helpers.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c handlers.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c modifiers.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c base.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters2.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters3.c

# Create static library
ar rcs libprintf.a _printf.o helpers.o handlers.o modifiers.o \
    base.o converters.o converters2.o converters3.o

# Compile main.c and link with library
gcc -Wall -Wextra -pedantic -std=gnu89 main.c -L. -lprintf -o printf_test

# Clean up
rm *.o
```

## Testing and Validation

### Compare with Standard printf

Create a comparison test file (`test_compare.c`):

```c
#include <stdio.h>
#include "main.h"

int main(void)
{
    int custom_len, std_len;

    printf("=== Comparing Custom vs Standard printf ===\n\n");

    /* Test 1: Simple string */
    custom_len = _printf("Custom: Hello, World!\n");
    std_len = printf("Standard: Hello, World!\n");
    printf("Custom length: %d, Standard length: %d\n\n", custom_len, std_len);

    /* Test 2: Integer */
    custom_len = _printf("Custom: %d\n", 42);
    std_len = printf("Standard: %d\n", 42);
    printf("Custom length: %d, Standard length: %d\n\n", custom_len, std_len);

    /* Test 3: Hex */
    custom_len = _printf("Custom: %x\n", 255);
    std_len = printf("Standard: %x\n", 255);
    printf("Custom length: %d, Standard length: %d\n\n", custom_len, std_len);

    return (0);
}
```

Compile and run:
```bash
gcc -Wall -Wextra -pedantic -std=gnu89 test_compare.c \
    _printf.c helpers.c handlers.c modifiers.c base.c \
    converters.c converters2.c converters3.c -o test_compare
./test_compare
```

### Memory Leak Testing with Valgrind

Install Valgrind:
```bash
sudo apt install valgrind -y
```

Run with Valgrind:
```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./printf_test
```

Expected output should show:
```
All heap blocks were freed -- no leaks are possible
```

## Common Errors and Solutions

### Error 1: `modifiers.c: In function 'print_width'`
```
modifiers.c:54:3: error: 'for' loop initial declarations are only allowed in C99 mode
```
**Solution:** Use `-std=gnu89` or `-std=c89` flag

### Error 2: `undefined reference to 'write'`
```
Solution: Make sure you're linking with the C standard library (should happen automatically)
```

### Error 3: Segmentation Fault
```bash
# Run with gdb to debug
gdb ./printf_test
(gdb) run
(gdb) backtrace
```

### Error 4: Buffer Overflow
```
Solution: The buffer is 1024 bytes and auto-flushes. Check _memcpy in helpers.c
```

## Performance Testing

Create a performance test (`perf_test.c`):

```c
#include <time.h>
#include <stdio.h>
#include "main.h"

int main(void)
{
    clock_t start, end;
    double cpu_time;
    int i;

    start = clock();
    for (i = 0; i < 10000; i++)
        _printf("Test %d: %s %x\n", i, "message", i);
    end = clock();

    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %f seconds\n", cpu_time);

    return (0);
}
```

## Integration in Your Own Projects

### Method 1: Direct Inclusion
Copy all source files to your project and compile together.

### Method 2: Using the Static Library
```bash
# After creating libprintf.a
gcc your_program.c -L/path/to/printf -lprintf -o your_program
```

### Method 3: Header-Only Access
```c
#include "main.h"

int main(void)
{
    _printf("Your formatted output: %d\n", 123);
    return (0);
}
```

## Additional Resources

- Betty style checker (if needed): https://github.com/holbertonschool/Betty
- C89 standard reference: https://www.open-std.org/jtc1/sc22/wg14/
- GCC documentation: https://gcc.gnu.org/onlinedocs/

## Clean Up

Remove compiled files:
```bash
rm -f printf_test test_compare perf_test *.o *.a
```

## Success Checklist

- [ ] WSL Ubuntu installed and updated
- [ ] `build-essential` package installed
- [ ] All source files present in project directory
- [ ] `main.c` test file created
- [ ] Project compiles without errors
- [ ] `printf_test` executable runs successfully
- [ ] Output matches expected format
- [ ] No memory leaks detected with Valgrind

---

## Quick Reference Card

```bash
# Compile
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o printf_test

# Run
./printf_test

# Debug
gdb ./printf_test

# Memory check
valgrind --leak-check=full ./printf_test

# Clean
rm printf_test *.o
```

Happy coding! 🚀