CC           = gcc
CFLAGS       = -Wall -Wextra -MMD -fpic
LDFLAGS      = -lm
SHARED_FLAGS = -shared

TARGETS          = myls
LIBNAME          = libmycmd.so
LIB_OBJS         = myls.o

INSTALL_LIB_PATH = /usr/local/lib
INSTALL_BIN_PATH = /usr/local/bin

all: $(LIBNAME) $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBNAME): $(LIB_OBJS)
	$(CC) $(SHARED_FLAGS) $^ -o $@ $(LDFLAGS)

myhello: myhello.o $(LIBNAME)
	$(CC) $^ -o $@ $(LDFLAGS)

myhello2: myhello2.o $(LIBNAME)
	$(CC) $^ -o $@ $(LDFLAGS)

install: $(LIBNAME) myhello
	sudo cp -f $(LIBNAME) $(INSTALL_LIB_PATH)
	sudo cp -f myhello $(INSTALL_BIN_PATH)
	sudo ldconfig

-include $(wildcard *.d)

clean:
	rm -f *.o *.d $(TARGETS) $(LIBNAME)

distclean: clean
	sudo rm -f $(INSTALL_LIB_PATH)/$(LIBNAME)
	sudo rm -f $(INSTALL_BIN_PATH)/myhello
	sudo ldconfig

.PHONY: all clean distclean install
