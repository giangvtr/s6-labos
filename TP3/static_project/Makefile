# Compiler and flags
CC=gcc
CFLAGS= -Wall -Wextra -MMD
LDFLAGS= -static
BUILDLIB=ar
LIBFLAGS=-rv
LDLIBS=libmyutil.a
myprogram= myhello
myprogram2= myhello2

# Default target
all: $(myprogram) $(myprogram2) $(LDLIBS)

#Construit la lib
$(LDLIBS): myfunc.o mytools.o
	$(BUILDLIB) $(LIBFLAGS) $@ $^

# Compiles the .c file into the corresponding .o file
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


# Rules for the final target program
$(myprogram): myfunc.o myhello.o mytools.o libmyutil.a
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(myprogram2): myfunc.o myhello2.o mytools.o libmyutil.a
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

include $(wildcard *.d)


# A clean target
clean :
	rm -f $ *.o
	rm -f *.d
	rm -f $(myprogram)
	rm -f $(myprogram2)
	rm -f *.a

