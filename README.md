# Custom Printf

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![C Standard](https://img.shields.io/badge/C-GNU89-green.svg)](https://gcc.gnu.org/)
[![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20WSL-lightgrey.svg)](https://www.linux.org/)

A feature-rich, custom implementation of the C standard library `printf` function, designed for educational purposes and to demonstrate advanced C programming concepts including variadic functions, buffered I/O, and modular software design.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [Compilation](#compilation)
- [Usage](#usage)
- [Supported Format Specifiers](#supported-format-specifiers)
- [Documentation](#documentation)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [Authors](#authors)

## Overview

This project implements a custom `_printf()` function that mimics the behavior of the standard C library's `printf()`. It features:

- **Buffered output** for efficient I/O operations (1024-byte buffer)
- **Modular architecture** with separation of concerns
- **Comprehensive format specifier support** including standard and custom specifiers
- **Robust error handling** and memory management
- **Extensive test coverage** demonstrating all features

The implementation is particularly useful for:
- Learning low-level C programming concepts
- Understanding variadic functions and format string parsing
- Exploring buffer management and system calls
- Building custom output formatting systems

## Features

### Standard Format Specifiers
- `%c` - Character output
- `%s` - String output
- `%d`, `%i` - Signed decimal integers
- `%u` - Unsigned decimal integers
- `%o` - Octal numbers
- `%x`, `%X` - Hexadecimal numbers (lowercase/uppercase)
- `%%` - Literal percent sign

### Custom Format Specifiers
- `%b` - Binary representation
- `%r` - Reversed string
- `%R` - ROT13 encoded string
- `%S` - String with non-printable characters escaped as `\xHH`
- `%p` - Pointer addresses

### Formatting Flags
- `+` - Always show sign for signed numbers
- `-` - Left-justify within field width
- ` ` (space) - Prefix space before positive numbers
- `#` - Alternate form (0x for hex, 0 for octal)
- `0` - Zero-padding for numeric values

### Width and Precision
- Minimum field width specification
- Precision for numeric and string values
- Dynamic width/precision using `*`

### Length Modifiers
- `h` - Short integer (converts to short)
- `l` - Long integer

## Project Structure

```
printf/
├── README.md                    # This file
├── LICENSE                      # Apache 2.0 License
├── Makefile                     # Build automation
│
├── main.h                       # Main header file with all declarations
│
├── _printf.c                    # Core printf implementation and entry point
├── helpers.c                    # Buffer management (init, memcpy, free)
├── handlers.c                   # Format string parsing (flags, width, precision)
├── modifiers.c                  # Width and alignment padding functions
├── base.c                       # Base conversion (_sbase, _ubase)
├── converters.c                 # Basic converters (%c, %s, %d, %i, %b)
├── converters2.c                # Numeric converters (%u, %o, %x, %X)
├── converters3.c                # Special converters (%S, %p, %r, %R)
│
├── main.c                       # Comprehensive test suite
│
├── docs/                        # Detailed documentation
│   ├── SETUP_GUIDE.md          # Setup and installation guide
│   ├── API_REFERENCE.md        # Complete API documentation
│   ├── ARCHITECTURE.md         # System architecture overview
│   ├── base_c.md               # base.c module documentation
│   ├── converters_c.md         # converters.c module documentation
│   ├── converters2_c.md        # converters2.c module documentation
│   ├── converters3_c.md        # converters3.c module documentation
│   ├── handlers_c.md           # handlers.c module documentation
│   ├── helpers_c.md            # helpers.c module documentation
│   ├── main_h.md               # main.h header documentation
│   └── modifiers_c.md          # modifiers.c module documentation
│
└── tests/                       # Test files
```

## Requirements

### System Requirements
- **Operating System**: Linux, macOS, or Windows Subsystem for Linux (WSL)
- **Compiler**: GCC 4.8 or later (with C89/GNU89 support)
- **Make**: GNU Make 3.81 or later (optional, for using Makefile)
- **Memory**: Minimum 512 MB RAM
- **Disk Space**: ~5 MB for source code and compilation

### Build Tools
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential

# CentOS/RHEL
sudo yum groupinstall "Development Tools"

# macOS
xcode-select --install
```

## Installation

### Clone the Repository

```bash
    git clone https://github.com/MercyKorir/printf.git
    cd printf
```

### Verify System Requirements

```bash
# Check GCC installation
gcc --version

# Check Make installation
make --version
```

## Compilation

### Method 1: Using Makefile (Recommended)

```bash
# Build the project
make

# Run the test suite
make run

# Clean build artifacts
make clean

# Rebuild from scratch
make re
```

### Method 2: Manual Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \
    main.c _printf.c helpers.c handlers.c modifiers.c \
    base.c converters.c converters2.c converters3.c \
    -o printf_test
```

### Method 3: Separate Compilation (for large projects)

```bash
# Compile each source file
gcc -Wall -Wextra -pedantic -std=gnu89 -c _printf.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c helpers.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c handlers.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c modifiers.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c base.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters2.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c converters3.c
gcc -Wall -Wextra -pedantic -std=gnu89 -c main.c

# Link all object files
gcc main.o _printf.o helpers.o handlers.o modifiers.o \
    base.o converters.o converters2.o converters3.o \
    -o printf_test

# Clean up
rm *.o
```

### Compiler Flags Explained

| Flag         | Purpose                                         |
|--------------|-------------------------------------------------|
| `-Wall`      | Enable all common compiler warnings             |
| `-Werror`    | Treat warnings as errors (ensures code quality) |
| `-Wextra`    | Enable additional warning flags                 |
| `-pedantic`  | Enforce strict ISO C compliance                 |
| `-std=gnu89` | Use GNU C89 standard (C89 with GNU extensions)  |

## Usage

### Basic Example

```c
#include "main.h"

int main(void)
{
    _printf("Hello, World!\n");
    _printf("The answer is %d\n", 42);
    _printf("Hexadecimal: %#x\n", 255);
    
    return (0);
}
```

### Advanced Examples

```c
#include "main.h"

int main(void)
{
    int num = 42;
    char *str = "Custom Printf";
    
    /* Basic formatting */
    _printf("Integer: %d\n", num);
    _printf("String: %s\n", str);
    _printf("Character: %c\n", 'A');
    
    /* Width and precision */
    _printf("Right-aligned: |%10d|\n", num);
    _printf("Left-aligned: |%-10d|\n", num);
    _printf("Zero-padded: %05d\n", num);
    _printf("Precision: %.5d\n", num);
    
    /* Flags */
    _printf("With plus: %+d\n", num);
    _printf("With space: % d\n", num);
    _printf("Hex with #: %#x\n", 255);
    
    /* Custom specifiers */
    _printf("Binary: %b\n", 42);
    _printf("Reversed: %r\n", "Hello");
    _printf("ROT13: %R\n", "Hello");
    _printf("Pointer: %p\n", (void *)&num);
    
    return (0);
}
```

### Compilation and Execution

```bash
# Compile your program with the printf library
gcc -Wall -Wextra -pedantic -std=gnu89 \
    your_program.c _printf.c helpers.c handlers.c modifiers.c \
    base.c converters.c converters2.c converters3.c \
    -o your_program

# Run
./your_program
```

### Supported Format Specifiers

| Specifier | Type      | Description                    | Example                  | Output      |
|-----------|-----------|--------------------------------|--------------------------|-------------|
| `%c`      | Character | Single character               | `_printf("%c", 'A')`     | `A`         |
| `%s`      | String    | Null-terminated string         | `_printf("%s", "Hello")` | `Hello`     |
| `%d`      | Integer   | Signed decimal                 | `_printf("%d", -42)`     | `-42`       |
| `%i`      | Integer   | Signed decimal (same as %d)    | `_printf("%i", 42)`      | `42`        |
| `%u`      | Unsigned  | Unsigned decimal               | `_printf("%u", 100)`     | `100`       |
| `%o`      | Octal     | Unsigned octal                 | `_printf("%o", 8)`       | `10`        |
| `%x`      | Hex       | Hex lowercase                  | `_printf("%x", 255)`     | `ff`        |
| `%X`      | Hex       | Hex uppercase                  | `_printf("%X", 255)`     | `FF`        |
| `%b`      | Binary    | Binary representation (custom) | `_printf("%b", 5)`       | `101`       |
| `%p`      | Pointer   | Pointer address                | `_printf("%p", ptr)`     | `0x7fff...` |
| `%r`      | String    | Reversed string (custom)       | `_printf("%r", "Hi")`    | `iH`        |
| `%R`      | String    | ROT13 encoded (custom)         | `_printf("%R", "Hi")`    | `Uv`        |
| `%S`      | String    | Escape non-printables (custom) | `_printf("%S", "A\x01")` | `A\x01`     |
| `%%`      | Literal   | Percent sign                   | `_printf("%%")`          | `%`         |

### Format Flag Combinations

```c
/* Flags: +, -, space, #, 0 */
_printf("%+d\n", 42);      // +42 (always show sign)
_printf("% d\n", 42);      // ␣42 (space for positive)
_printf("%#x\n", 255);     // 0xff (alternate form)
_printf("%05d\n", 42);     // 00042 (zero padding)
_printf("%-10d\n", 42);    // 42␣␣␣␣␣␣␣␣ (left justify)

/* Width and precision */
_printf("%10s\n", "Hi");   // ␣␣␣␣␣␣␣␣Hi (min width 10)
_printf("%.3s\n", "Hello"); // Hel (max 3 chars)
_printf("%10.3s\n", "Hello"); // ␣␣␣␣␣␣␣Hel (width 10, precision 3)

/* Length modifiers */
_printf("%ld\n", 123456789L);    // Long int
_printf("%hd\n", (short)42);     // Short int
```

## Documentation

Comprehensive documentation is available in the `docs/` directory:

- **[SETUP_GUIDE.md](docs/SETUP_GUIDE.md)** - Detailed installation and setup instructions
- **[API_REFERENCE.md](docs/API_REFERENCE.md)** - Complete API documentation
- **[ARCHITECTURE.md](docs/ARCHITECTURE.md)** - System design and architecture overview

### Module Documentation

Each module has dedicated documentation:

- **[main_h.md](docs/main_h.md)** - Header file documentation (types, macros, prototypes)
- **[_printf.c](docs/_printf_c.md)** - Core printf implementation
- **[helpers_c.md](docs/helpers_c.md)** - Buffer management functions
- **[handlers_c.md](docs/handlers_c.md)** - Format string parsing logic
- **[modifiers_c.md](docs/modifiers_c.md)** - Width and padding functions
- **[base_c.md](docs/base_c.md)** - Base conversion algorithms
- **[converters_c.md](docs/converters_c.md)** - Basic format specifiers
- **[converters2_c.md](docs/converters2_c.md)** - Numeric format specifiers
- **[converters3_c.md](docs/converters3_c.md)** - Custom format specifiers

## Testing

### Running the Test Suite

```bash
# Using Makefile
make run

# Or manually
./printf_test
```

### Memory Leak Detection

```bash
# Install Valgrind
sudo apt install valgrind

# Run memory check
valgrind --leak-check=full --show-leak-kinds=all ./printf_test
```

Expected output:
```
All heap blocks were freed -- no leaks are possible
```

### Creating Custom Tests

```c
#include "main.h"

int main(void)
{
    int len;
    
    /* Test return value */
    len = _printf("Test\n");
    _printf("Printed %d characters\n", len);
    
    /* Test edge cases */
    _printf("NULL string: %s\n", NULL);
    _printf("Empty string: %s\n", "");
    _printf("INT_MAX: %d\n", 2147483647);
    _printf("INT_MIN: %d\n", -2147483648);
    
    return (0);
}
```

## Contributing

Contributions are welcome! Please follow these guidelines:

### How to Contribute

1. **Fork the repository**
   ```bash
   git clone https://github.com/YourUsername/printf.git
   cd printf
   ```

2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make your changes**
   - Follow the existing code style
   - Add tests for new features
   - Update documentation as needed
   - Ensure all tests pass

4. **Commit your changes**
   ```bash
   git add .
   git commit -m "Add: brief description of changes"
   ```

5. **Push to your fork**
   ```bash
   git push origin feature/your-feature-name
   ```

6. **Open a Pull Request**
   - Provide a clear description of the changes
   - Reference any related issues
   - Wait for review and address feedback

### Code Style Guidelines

- Follow the **Betty** coding style
- Use meaningful variable and function names
- Add comments for complex logic
- Keep functions focused and concise
- Maintain consistent indentation (tabs or spaces)

### Testing Requirements

- All new features must include tests
- Ensure no memory leaks (verify with Valgrind)
- Code must compile without warnings using all flags

## License

This project is licensed under the **Apache License 2.0** - see the [LICENSE](LICENSE) file for details.

```
Copyright 2024 Mercy Korir

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

## Acknowledgments

- Inspired by the C standard library `printf` implementation
- Educational project for learning systems programming
- Built with guidance from ALX Software Engineering program

## Support

For questions, issues, or suggestions:

- **Issue Tracker**: [GitHub Issues](https://github.com/MercyKorir/printf/issues)
- **Discussions**: [GitHub Discussions](https://github.com/MercyKorir/printf/discussions)