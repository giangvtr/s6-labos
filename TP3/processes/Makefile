# ------------------------------
# Compiler and flags
# ------------------------------
CC = gcc
CFLAGS = -Wall -pedantic-errors
LDFLAGS =
LDLIBS =
PROGRAMS = myenv myexec-test myfork-test myexec

.PHONY: all clean
all: $(PROGRAMS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGRAMS): %: %.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

-include $(wildcard *.d)

clean:
	rm -f *.o *.d $(PROGRAMS)

