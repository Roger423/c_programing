#
# Makefile for the Student Management System project
#

# Compiler and compiler flags
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99

# --- Directory Setup ---
# All generated files will go into this directory
BUILD_DIR = build

# The name of the final executable
TARGET_NAME = student_system
TARGET = $(BUILD_DIR)/$(TARGET_NAME)

# --- Source and Object File Setup ---
# Find all .c source files
SRCS = $(wildcard *.c)

# Generate the list of object files that will be placed in the BUILD_DIR
# e.g., "main.c add.c" becomes "build/main.o build/add.o"
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target: 'all'
.PHONY: all
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	# Create the build directory if it doesn't exist.
	# The '@' symbol suppresses the command from being printed to the console.
	# 'mkdir -p' creates parent directories as needed and doesn't fail if the directory already exists.
	@mkdir -p $(BUILD_DIR)
	# Link the object files
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule to compile a .c file into a .o file inside the BUILD_DIR
# This rule tells make: to create a file like 'build/main.o', find the corresponding 'main.c'
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	# Compile the source file
	# $< is the first prerequisite (the .c file)
	# $@ is the target (the .o file)
	$(CC) $(CFLAGS) -c $< -o $@

# 'clean' target
# Removes the entire build directory, which is much cleaner.
.PHONY: clean
clean:
	@echo "Cleaning up build files..."
	rm -rf $(BUILD_DIR)
