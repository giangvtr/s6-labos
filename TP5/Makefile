# ------------------------------
# Compiler & Linker Configuration
# ------------------------------

CC           = gcc
CFLAGS       = -Wall -Wextra -MMD -fPIC       # -fPIC: position-independent code (for shared lib)
LDFLAGS      = -shared                        # Used when building the shared lib
LDLIBS       = -lfatutils                     # Linker will look for libfatutils.so
LIB_PATH     = -L.                            # Look in current dir for libs

# ------------------------------
# Targets & Files
# ------------------------------

TARGET_LIB   = libfatutils.so                 # Shared library
TARGETS      = off2clust saveclust            # Executables

LIB_SRC      = libfatutils.c
LIB_HDR      = libfatutils.h
LIB_OBJ      = libfatutils.o

PREFIX       = /usr/local
INSTALL_LIB  = $(PREFIX)/lib
INSTALL_INC  = $(PREFIX)/include
INSTALL_BIN  = $(PREFIX)/bin

# ------------------------------
# Default Target
# ------------------------------

all: $(TARGET_LIB) $(TARGETS)

# ------------------------------
# Pattern Rule: Compile .c -> .o
# ------------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------
# Build Shared Library
# ------------------------------

$(TARGET_LIB): $(LIB_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

# ------------------------------
# Build Executables
# ------------------------------

off2clust: off2clust.o $(TARGET_LIB)
	$(CC) $< -o $@ $(LIB_PATH) $(LDLIBS)

saveclust: saveclust.o $(TARGET_LIB)
	$(CC) $< -o $@ $(LIB_PATH) $(LDLIBS)

# ------------------------------
# Install Targets
# ------------------------------

install: $(TARGET_LIB) $(LIB_HDR) $(TARGETS)
	sudo cp -f $(TARGET_LIB) $(INSTALL_LIB)
	sudo cp -f $(LIB_HDR) $(INSTALL_INC)
	sudo cp -f $(TARGETS) $(INSTALL_BIN)
	sudo ldconfig

# ------------------------------
# Clean Targets
# ------------------------------

clean:
	rm -f *.o *.d $(TARGET_LIB) $(TARGETS)

distclean: clean
	sudo rm -f $(INSTALL_LIB)/$(TARGET_LIB)
	sudo rm -f $(INSTALL_INC)/$(LIB_HDR)
	sudo rm -f $(INSTALL_BIN)/off2clust $(INSTALL_BIN)/saveclust
	sudo ldconfig

# ------------------------------
# Distribution Archive
# ------------------------------

dist:
	zip tp5_archive.zip *.c *.h Makefile *.txt *.md

# ------------------------------
# Dependency Includes
# ------------------------------

-include $(wildcard *.d)

# ------------------------------
# Phony Targets
# ------------------------------

.PHONY: all clean distclean install dist


# make clean
# make && sudo make install
# ./off2clust
# off2clust