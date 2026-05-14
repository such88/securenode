# ==============================
# Configurable Variables
# ==============================

# Path to GCC (change if GCC is not in PATH)
GCC := /usr/bin/gcc

# Compiler flags: -Wall (all warnings), -Wextra (extra warnings), -O2 (optimize)
CFLAGS := -Wall -Wextra -O2

# List of source files
SRC := gen_cgpa_pkg_data.c
SRC += single_lr.c

# Object files (replace .c with .o)
OBJ := $(SRC:.c=.o)

# Output executable name
TARGET := my_program

# ==============================
# Build Rules
# ==============================

# Default target
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJ)
	@echo "Linking..."
	$(GCC) $(CFLAGS) -o $@ $^

# Compile each .c file into .o
%.o: %.c
	@echo "Compiling $<..."
	$(GCC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	@echo "Cleaning up..."
	rm -f $(OBJ) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# ==============================
# Phony Targets
# ==============================
.PHONY: all clean run
