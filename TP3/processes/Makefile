# Compiler and flags
CC=gcc
CFLAGS= -Wall -pedantic-errors
LDFLAGS= 
LDLIBS=
myprogram=myenv
myprogram2=myexec-test
myprogram3=myfork-test


# Default target
all: $(myprogram) $(myprogram2) $(myprogram3)

# Compiles the .c file into the corresponding .o file
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Rules for the final target program
$(myprogram): $(myprogram).o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(myprogram2): $(myprogram2).o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(myprogram3): $(myprogram3).o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Tells make to include these dependency files. This ensures make knows which header files
# each .o file depends on, so it can rebuild files when headers are updated.
include $(wildcard *.d)


# A phony target that deletes all generated files, exclude given files
clean :
	rm -f $ *.o
	rm -f *.d
	rm -f $(myprogram)
	rm -f $(myprogram2)
	rm -f $(myprogram3)
