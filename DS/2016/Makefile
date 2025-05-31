CC           = gcc
CFLAGS       = -Wall -Wextra -MMD -fPIC       # -fPIC: position-independent code (for shared lib)
LDFLAGS      = -shared                        # Used when building the shared lib
LDLIBS       = -lmycmd                   # Linker will look for libmycmd.so
LIB_PATH     = -L.                            # Look in current dir for libs

TARGET_LIB   = libmycmd.so                 # Shared library
TARGETS      = main         			   # Executables

LIB_HDR      = myls.h
LIB_OBJ      = myls.o

PREFIX       = /usr/local
INSTALL_LIB  = $(PREFIX)/lib
INSTALL_INC  = $(PREFIX)/include
INSTALL_BIN  = $(PREFIX)/bin

all: $(TARGET_LIB) $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_LIB): $(LIB_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

main: main.o $(TARGET_LIB)
	$(CC) $< -o $@ $(LIB_PATH) $(LDLIBS)

install: $(TARGET_LIB) $(LIB_HDR) $(TARGETS)
	sudo cp -f $(TARGET_LIB) $(INSTALL_LIB)
	sudo cp -f $(LIB_HDR) $(INSTALL_INC)
	sudo cp -f $(TARGETS) $(INSTALL_BIN)
	sudo ldconfig

clean:
	rm -f *.o *.d $(TARGET_LIB) $(TARGETS)

distclean: clean
	sudo rm -f $(INSTALL_LIB)/$(TARGET_LIB)
	sudo rm -f $(INSTALL_INC)/$(LIB_HDR)
	sudo rm -f $(INSTALL_BIN)/main
	sudo ldconfig

report:
	tar -czvf os-vugiang.tar.gz 2016-report.txt *.c

-include $(wildcard *.d)

.PHONY: all clean distclean install report

