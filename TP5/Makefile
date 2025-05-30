# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -MMD -fPIC
LDFLAGS = -shared
TARGET_LIB = libfatutils.so
TARGET_BIN1=off2clust
TARGET_BIN2=saveclust

LIB_SRC = libfatutils.c
LIB_HEADER = libfatutils.h
LIB_OBJ = libfatutils.o

PREFIX = /usr/local
LD_LIBRARY_PATH = $(PREFIX)/lib
INCLUDE_PATH = $(PREFIX)/include
BIN_PATH = $(PREFIX)/bin

# Default target
all: $(TARGET_LIB) $(TARGET_BIN1) $(TARGET_BIN2)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build the shared library
$(TARGET_LIB): $(LIB_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# Build the binary (link with the library)
$(TARGET_BIN1): $(TARGET_BIN1).o $(LIB_HEADER) $(TARGET_LIB)
	$(CC) off2clust.o -L. -lfatutils -o $@
# -L. tells the linker to add "current dir" to its list of directories to search for libraries.
# -lfatutils means: look for a library named libfatutils.so or libfatutils.a

$(TARGET_BIN2): $(TARGET_BIN2).o $(LIB_HEADER) $(TARGET_LIB)
	$(CC) $(TARGET_BIN2).o -L. -lfatutils -o $@
# -L. tells the linker to add "current dir" to its list of directories to search for libraries.
# -lfatutils means: look for a library named libfatutils.so or libfatutils.a


# Install library, header, and binary
install: $(TARGET_LIB) $(LIB_HEADER) $(TARGET_BIN1) $(TARGET_BIN2)
	sudo cp -f $(TARGET_LIB) $(LD_LIBRARY_PATH)
	sudo cp -f $(LIB_HEADER) $(INCLUDE_PATH)
	sudo ldconfig

# Clean build files
clean:
	rm -f *.o *.d $(TARGET_LIB) $(TARGET_BIN1) $(TARGET_BIN2)

# Remove installed files
distclean: clean
	sudo rm -f $(LD_LIBRARY_PATH)/$(TARGET_LIB)
	sudo rm -f $(INCLUDE_PATH)/$(LIB_HEADER)
	sudo ldconfig

# Create a distribution archive
dist:
	zip tp5_archive.zip *.c *.h Makefile *.txt *.md

# Include auto-generated dependencies
-include $(wildcard *.d)

.PHONY: all clean install distclean dist

# make clean
# make && sudo make install
# ./off2clust
# off2clust