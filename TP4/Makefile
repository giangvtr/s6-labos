# Compiler and flags
CC=gcc
CFLAGS= -Wall -pedantic-errors
LDFLAGS= 
LDLIBS=
myprogram=my_wc
BIN_INSTALL_PATH=/usr/local/bin/

# Default target
all: $(myprogram)

# Compiles the .c file into the corresponding .o file
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rules for the final target program
$(myprogram): $(myprogram).o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

install: $(myprogram) $(BIN_INSTALL_PATH)
	sudo cp -f $(myprogram) $(BIN_INSTALL_PATH)
	sudo ldconfig

# Tells make to include these dependency files. This ensures make knows which header files
# each .o file depends on, so it can rebuild files when headers are updated.
include $(wildcard *.d)

# A phony target that deletes all generated files, exclude given files
clean:
	rm -f $ *.o
	rm -f *.d
	rm -f $(myprogram)
	
distclean:
	sudo rm -f $(BIN_INSTALL_PATH)/$(myprogram)