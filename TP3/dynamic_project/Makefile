# Compiler and flags
CC=gcc
CFLAGS= -Wall -Wextra -MMD -fpic
LDFLAGS=-lm
LDLIBS=libmyutils.so
LD_LIBRARY_PATH=/usr/local/lib
BIN_INSTALL_PATH=/usr/local/bin
myprogram= myhello
myprogram2= myhello2

# Default target
all: $(myprogram) $(myprogram2) $(LDLIBS)


# Compiles the .c file into the corresponding .o file
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Build the library
$(LDLIBS): myfunc.o mytools.o 
	$(CC) -shared $^ -o $(LDLIBS) $(LDFLAGS)


# Rules for the final target program
$(myprogram): myhello.o myfunc.o mytools.o $(LDLIBS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(myprogram2): myfunc.o myhello2.o mytools.o $(LDLIBS)
	$(CC) $^ $(LDLIBS) -o $@ $(LDFLAGS)

install: $(LDLIBS) $(myprogram)
	sudo mv -f $(LDLIBS) $(LD_LIBRARY_PATH)
	sudo cp -f $(myprogram) $(BIN_INSTALL_PATH)
	sudo ldconfig

# Tells make to include these dependency files. This ensures make knows which header files
# each .o file depends on, so it can rebuild files when headers are updated.
include $(wildcard *.d)


# A phony target that deletes all generated files, exclude given files
clean :
	rm -f *.o
	rm -f *.d
	rm -f $(myprogram)
	rm -f $(myprogram2)

distclean: clean
	sudo rm -f $(LD_LIBRARY_PATH)/$(myprogram)
	sudo rm -f $(BIN_INSTALL_PATH)/$(myprogram)
	sudo ldconfig


#TO BUILD THE PROGRAM
# make clean
# make && sudo make install
# ./myhello
# myhello
