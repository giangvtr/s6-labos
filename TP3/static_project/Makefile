# --------------------------
# Compiler and Archiver Setup
# --------------------------

CC       = gcc                 # C compiler
CFLAGS   = -Wall -Wextra -MMD  # Compiler flags: all warnings + dependency generation
LDFLAGS  = -static             # Linker flags: force static linking
AR       = rv                  # Archiver tool to build static libraries
ARFLAGS  = rcs                 # Flags for 'ar': replace, create index, be silent

# --------------------------
# File Definitions
# --------------------------

LIBNAME     = libmyutil.a           # Static library output
LIBOBJECTS  = myfunc.o mytools.o    # Object files for the static library
TARGETS     = myhello myhello2      # Final executables

# --------------------------
# Default Rule: Build everything
# --------------------------

all: $(TARGETS)

# --------------------------
# Static Library Rule
# --------------------------

#Equivalent: ar -rv libmyutil.a myfunc.o mytools.o
$(LIBNAME): $(LIBOBJECTS)
	$(AR) $(ARFLAGS) $@ $^

# --------------------------
# Pattern Rule: Compile .c -> .o
# --------------------------

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# --------------------------
# Link Targets with Static Library
# --------------------------
# Equivalent: gcc myhello.o libmyutil.a -o myhello

myhello: myhello.o $(LIBNAME)
	$(CC) $(LDFLAGS) $^ -o $@

myhello2: myhello2.o $(LIBNAME)
	$(CC) $(LDFLAGS) $^ -o $@


# --------------------------
# Include auto-generated dependency files
# --------------------------

-include $(wildcard *.d)

# --------------------------
# Clean Rule
# --------------------------

clean:
	rm -f *.o *.d *.a $(TARGETS)

