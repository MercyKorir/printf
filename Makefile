# Makefile for Custom Printf Project
# Compatible with WSL Ubuntu and Linux systems

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
DEBUG_FLAGS = -g
OPTIMIZATION = -O2

# Source files
SRCS = _printf.c helpers.c handlers.c modifiers.c base.c \
       converters.c converters2.c converters3.c

# Object files
OBJS = $(SRCS:.c=.o)

# Test file
TEST_SRC = main.c
TEST_OBJ = main.o

# Output executable
TARGET = printf_test

# Library name
LIB = libprintf.a

# Default target
all: $(TARGET)

# Compile the main executable
$(TARGET): $(OBJS) $(TEST_OBJ)
	@echo "Linking $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJ) -o $(TARGET)
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile source files to object files
%.o: %.c main.h
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library
lib: $(OBJS)
	@echo "Creating static library $(LIB)..."
	ar rcs $(LIB) $(OBJS)
	@echo "Library created successfully!"

# Compile with debugging symbols
debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)
	@echo "Debug build complete. Run with: gdb ./$(TARGET)"

# Compile with optimizations
optimized: CFLAGS += $(OPTIMIZATION)
optimized: clean $(TARGET)
	@echo "Optimized build complete!"

# Run the program
run: $(TARGET)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

# Run with valgrind for memory leak detection
valgrind: $(TARGET)
	@echo "Running valgrind memory check..."
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Test target - compile and run comparison test
test: $(OBJS)
	@echo "Creating comparison test..."
	$(CC) $(CFLAGS) test_compare.c $(OBJS) -o test_compare
	@echo "Running comparison test..."
	@./test_compare

# Clean object files and executable
clean:
	@echo "Cleaning build files..."
	rm -f $(OBJS) $(TEST_OBJ) $(TARGET) $(LIB) test_compare perf_test
	@echo "Clean complete!"

# Clean everything including backup files
fclean: clean
	@echo "Deep cleaning..."
	rm -f *~ *.swp *.swo
	@echo "Deep clean complete!"

# Rebuild from scratch
re: fclean all

# Check for coding style (Betty checker)
betty:
	@echo "Running Betty style checker..."
	@betty *.c *.h || echo "Betty checker not installed. Install with: sudo apt install betty"

# Show help
help:
	@echo "Custom Printf Project Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all        - Build the project (default)"
	@echo "  lib        - Create static library (libprintf.a)"
	@echo "  debug      - Build with debug symbols"
	@echo "  optimized  - Build with optimizations"
	@echo "  run        - Build and run the program"
	@echo "  test       - Run comparison tests"
	@echo "  valgrind   - Run with memory leak detection"
	@echo "  clean      - Remove object files and executable"
	@echo "  fclean     - Remove all generated files"
	@echo "  re         - Rebuild from scratch"
	@echo "  betty      - Check coding style"
	@echo "  help       - Show this help message"
	@echo ""
	@echo "Usage examples:"
	@echo "  make              # Build the project"
	@echo "  make run          # Build and run"
	@echo "  make debug        # Build with debugging"
	@echo "  make clean        # Clean build files"

# Phony targets (not actual files)
.PHONY: all lib debug optimized run valgrind test clean fclean re betty help