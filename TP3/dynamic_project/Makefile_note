# ------------------------------
# Compiler & Linker Configuration
# ------------------------------

CC           = gcc
CFLAGS       = -Wall -Wextra -MMD -fpic    # -fpic to make compiled code relocatable in memory
LDFLAGS      = -lm                         # Linker flags (e.g., math lib)
SHARED_FLAGS = -shared			   # Used when building shared lib		

# ------------------------------
# File and Path Setup
# ------------------------------

TARGETS          = myhello myhello2        # Executables
LIBNAME          = libmyutils.so           # Shared library
LIB_OBJS         = myfunc.o mytools.o      # Object files for the shared library

INSTALL_LIB_PATH = /usr/local/lib	   # Where to install the .so
INSTALL_BIN_PATH = /usr/local/bin          # Where to install executables (in install target)

# ------------------------------
# Default Target: Build All
# ------------------------------

all: $(LIBNAME) $(TARGETS)		   # Default make when used with no args

# ------------------------------
# Pattern Rule: Compile .c -> .o
# Eq : gcc -Wall -Wextra -MMD -fpic -c file.c -o file.o
# -c flag for compile only, dont link
# ------------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------
# Build Shared Library
# Eq: gcc -shared myfunc.o mytools.o -o libmyutils.so
# ------------------------------

$(LIBNAME): $(LIB_OBJS)
	$(CC) $(SHARED_FLAGS) $^ -o $@ $(LDFLAGS)

# ------------------------------
# Build Executables (Link Against Shared Library)
# ------------------------------

myhello: myhello.o $(LIBNAME)
	$(CC) $^ -o $@ $(LDFLAGS)

myhello2: myhello2.o $(LIBNAME)
	$(CC) $^ -o $@ $(LDFLAGS)

# ------------------------------
# Install Targets
# ------------------------------

install: $(LIBNAME) myhello
	sudo cp -f $(LIBNAME) $(INSTALL_LIB_PATH)
	sudo cp -f myhello $(INSTALL_BIN_PATH)
	sudo ldconfig   # Updates the dynamic linker run-time bindings

# ------------------------------
# Dependency Includes
# ------------------------------
# Automatically include generated dependency files

-include $(wildcard *.d)

# ------------------------------
# Clean Targets
# ------------------------------

clean:
	rm -f *.o *.d $(TARGETS) $(LIBNAME)

distclean: clean
	sudo rm -f $(INSTALL_LIB_PATH)/$(LIBNAME)
	sudo rm -f $(INSTALL_BIN_PATH)/myhello
	sudo ldconfig

# ------------------------------
# Phony Targets
# Declares that these targets don’t produce real files. Prevents Make from getting confused if a file named install exists, for example.
# ------------------------------

.PHONY: all clean distclean install


