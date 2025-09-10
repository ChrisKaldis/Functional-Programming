# =============================================================================
# Generic Makefile for compiling C99 programs from multiple subdirectories
#
# To Use:
#   make : Compiles all .c files from all lab directories.
#   make clean : Removes all compiled files.
#   make bin/program_name : Compiles a single, specific program. 
# 	(e.g., 'make bin/hello' to compile a file named hello.c)
# =============================================================================

# 1. VARIABLES

# Set the compiler and flags
CC = gcc
# Use C99 standard, show all warnings, and include debug info.
CFLAGS = -std=c99 -Wall -g

# Define the source and build directories.
SRCDIR = lab01 lab02 lab03 lab04 lab05
BUILDDIR = bin

# Use VPATH to tell 'make' where to find the source files.
# This is the standard way to handle multiple source directories.
VPATH = $(SRCDIR)

# Find all files ending in .c in ALL of the source directories.
# The 'foreach' function iterates through each directory in SRCDIR.
SOURCES := $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.c))

# Define the executable files based on the source files found.
# It takes the base name of each source file (e.g., 'hello.c' from 'lab01/hello.c')
# and maps it to an executable in the build directory (e.g., 'bin/hello').
EXECUTABLES := $(patsubst %.c,$(BUILDDIR)/%,$(notdir $(SOURCES)))

# 2. TARGETS

# The 'all' target is the default and depends on all executables.
.PHONY: all
all: $(EXECUTABLES)

# This pattern rule tells 'make' how to build an executable in BUILDDIR
# from a corresponding .c file found in one of the VPATH directories.
#
# $@ is the target name (e.g., bin/hello).
# $< is the source file name (e.g., lab01/hello.c).
$(BUILDDIR)/%: %.c
	@mkdir -p $(BUILDDIR)
	@echo "Compiling $<  ->  $@ ..."
	$(CC) $(CFLAGS) -o $@ $<

# The 'clean' target removes the build directory and all its contents.
.PHONY: clean
clean:
	@echo "Cleaning up build directory..."
	rm -rf $(BUILDDIR)