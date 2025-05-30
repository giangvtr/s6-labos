# Compiler and flags
CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS= -static
LDLIBS=
myprogram= myhello
myprogram2= myhello2


# Default target
all: $(myprogram) $(myprogram2)


# Question 1.3:
# The target "all: network" ensures that when "make" is executed without specifying a target,
# the program "network" will be built. This is useful for convenience, as it allows users to simply run
# "make" instead of "make network". It also centralizes the build process in case there are multiple
# default targets.


# Compiles the .c file into the corresponding .o file
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Rules for the final target program
$(myprogram): myfunc.o myhello.o mytools.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(myprogram2): myfunc.o myhello2.o mytools.o
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
