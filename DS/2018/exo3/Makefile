CC= gcc
CFLAGS=-Wall -Wextra -MMD      # -fPIC: position-independent code (for shared lib)
LDFLAGS=-static
LDFLAGS  = -static             # Linker flags: force static linking
AR       = ar                  # Archiver tool to build static libraries
ARFLAGS  = -rv

TARGETS=my_ls         			   # Executables
LIBNAME     = libmyprocessdir.a           # Static library output
LIBOBJECTS  = process_dir.o my_concat.o    # Object files for the static library

INSTALL_LIB_PATH = /usr/local/lib

all: $(TARGETS) $(LIBNAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Equivalent: ar -rv libmyutil.a myfunc.o mytools.o
$(LIBNAME): $(LIBOBJECTS)
	$(AR) $(ARFLAGS) $@ $^

# Rules for the final target program
$(TARGETS): my_ls.o $(LIBNAME)
	$(CC) $(LDFLAGS) $^ -o $@

install: $(LIBNAME)
	sudo cp -f $(LIBNAME) $(INSTALL_LIB_PATH)
	sudo ldconfig

clean:
	rm -f *.o *.d $(TARGETS) $(LIBNAME)

distclean: clean
	sudo rm -f $(INSTALL_LIB_PATH)/$(LIBNAME)

-include $(wildcard *.d)

.PHONY: all clean distclean install
