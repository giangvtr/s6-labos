CC= gcc
CFLAGS=-Wall -Wextra -MMD
LDFLAGS=-static
LDFLAGS  = -static             # Linker flags: force static linking
AR       = ar                  # Archiver tool to build static libraries
ARFLAGS  = -rv

TARGETS=myhexdump         			   		  # Executables
LIBNAME     = libmyprintfile.a           # Static library output
LIBOBJECTS  = print_file.o   # Object files for the static library

INSTALL_BIN_PATH = /usr/local/bin

all: $(TARGETS) $(LIBNAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Equivalent: ar -rv libmyutil.a myfunc.o mytools.o
$(LIBNAME): $(LIBOBJECTS)
	$(AR) $(ARFLAGS) $@ $^

# Rules for the final target program
$(TARGETS): myhexdump.o $(LIBNAME)
	$(CC) $(LDFLAGS) $^ -o $@

install: $(TARGETS)
	sudo cp -f $(TARGETS) $(INSTALL_BIN_PATH)
	sudo ldconfig

clean:
	rm -f *.o *.d $(TARGETS) $(LIBNAME)

distclean: clean
	sudo rm -f $(INSTALL_BIN_PATH)/$(TARGETS)

-include $(wildcard *.d)

.PHONY: all clean distclean install
