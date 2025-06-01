# Fiche for DS TPS6-OS

## Makefile for static library
```makefile
CC      = gcc
CFLAGS  = -Wall -Wextra -MMD
LDFLAGS = -static
AR      = ar
ARFLAGS = -rv

TARGETS = my_ls
LIBNAME = libmyprocessdir.a
LIBOBJECTS = process_dir.o my_concat.o
HEADERS = process_dir.h my_concat.h

INSTALL_LIB_PATH = /usr/local/lib
INSTALL_BIN_PATH = /usr/local/bin
INSTALL_INC_PATH = /usr/local/include

all: $(TARGETS) $(LIBNAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBNAME): $(LIBOBJECTS)
	$(AR) $(ARFLAGS) $@ $^

$(TARGETS): my_ls.o $(LIBNAME)
	$(CC) $(LDFLAGS) $^ -o $@

install: $(TARGETS) $(LIBNAME)
	sudo cp -f $(LIBNAME) $(INSTALL_LIB_PATH)/
	sudo cp -f $(TARGETS) $(INSTALL_BIN_PATH)/
	sudo cp -f $(HEADERS) $(INSTALL_INC_PATH)/
	sudo ldconfig

clean:
	rm -f *.o *.d $(TARGETS) $(LIBNAME)

distclean: clean
	sudo rm -f $(INSTALL_LIB_PATH)/$(LIBNAME) $(INSTALL_BIN_PATH)/$(TARGETS)
	sudo rm -f $(INSTALL_INC_PATH)/$(HEADERS)

-include $(wildcard *.d)

.PHONY: all clean distclean install

```

## Makefile for dynamic library
```makefile
CC           = gcc
CFLAGS       = -Wall -Wextra -MMD -fpic
LDFLAGS      = -L. -lmycmd -lm
SHARED_FLAGS = -shared

LIBNAME      = libmycmd.so
LIB_OBJS     = myls.o

EXECUTABLES  = myhello myhello2

INSTALL_LIB_PATH = /usr/local/lib
INSTALL_BIN_PATH = /usr/local/bin

all: $(LIBNAME) $(EXECUTABLES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBNAME): $(LIB_OBJS)
	$(CC) $(SHARED_FLAGS) $^ -o $@

myhello: myhello.o $(LIBNAME)
	$(CC) $< -o $@ $(LDFLAGS)

myhello2: myhello2.o $(LIBNAME)
	$(CC) $< -o $@ $(LDFLAGS)

install: $(LIBNAME) $(EXECUTABLES)
	sudo cp -f $(LIBNAME) $(INSTALL_LIB_PATH)
	sudo cp -f $(EXECUTABLES) $(INSTALL_BIN_PATH)
	sudo ldconfig

-include $(wildcard *.d)

clean:
	rm -f *.o *.d $(EXECUTABLES) $(LIBNAME)

distclean: clean
	sudo rm -f $(INSTALL_LIB_PATH)/$(LIBNAME)
	sudo rm -f $(addprefix $(INSTALL_BIN_PATH)/,$(EXECUTABLES))
	sudo ldconfig

.PHONY: all clean distclean install

```

## Command line arguments
```c++
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>      // For errno, perror, strerror
int main(int argc, char **argv, char **envp) {
    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int index;
    int c;

    opterr = 0;

    // Parse command-line options
    while ((c = getopt(argc, argv, "abc:")) != -1) {
        switch (c) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case '?':
                //Stores the option character that caused an error during command-line argument parsing.
                if (optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue ? cvalue : "(null)");
    
    //To make sure always have arguments. Ortherwise bad address error because accessing NULL characters
    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n size] [-a] filename\n", nomprog);
        return 1;
    }
    
    // Print non-option arguments
    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);

    // Example: Store environment variables for future use
    extern char **environ;
    char **env = envp ? envp : environ;

    printf("\nEnvironment variables (first 3 for example):\n");
    for (int i = 0; env[i] != NULL && i < 3; i++) {
        printf("%s\n", env[i]);
    }

    // Example of using errno, perror, strerror
    // If -c was given, try to open the file (or pretend to)
    if (cvalue != NULL) {
        FILE *file = fopen(cvalue, "r");
        if (file == NULL) {
            // perror prints the error message to stderr
            perror("fopen");
            // strerror gives the error string (you can print it yourself)
            fprintf(stderr, "Error opening '%s': %s\n", cvalue, strerror(errno));
            return 1;
        } else {
            printf("Successfully opened '%s'\n", cvalue);
            fclose(file);
        }
    }

    return 0;
}
```

## Handle error
* errno: Use when you want the raw error code. just an integer variable; it does not output anything by itself
```c++
#include <errno.h>
printf("Error code: %d\n", errno);
//Output: Error code: 2
```

* perror(): Use for simple, formatted error messages to stderr. Always writes to stderr.
```c++
#include <stdio.h>
#include <errno.h>
perror("Failed to open file");
//Output: Failed to open file: No such file or directory
```
* strerror(): Use when you want to print or manipulate the error description yourself. strerror(errno) returns a string describing the error, but does not print anything.
```c++
#include <stdio.h>
#include <errno.h>
#include <string.h>
printf("Error: %s\n", strerror(errno));
//Error: No such file or directory
```

