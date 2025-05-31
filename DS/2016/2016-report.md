# REPORT FOR DSTP-OS-2016
**Author** : VU Giang

Q1.1) ls -l | egrep ^.r

Q1.2) ls -l | egrep ^.r--

Q1.3) ls -all | egrep ^.r..-..-..

### Q3.1) 
```c++
int ls_dir(char * dirname) {
    return execl("/bin/ls", "ls", "-l", dirname, NULL);
}
```

### Q3.2)
```makefile
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
```

### Q3.3) 
**Output**: ls: cannot access '/home/user': No such file or directory
* 'user' will depend on session and machine, in my machine it should be /home/giangvu or home/eii
Otherwise, use environment variable like $HOME by getenv("HOME")

### Q3.4)
* Modify your code in order to display detailed information the entries of the current directory
  if the option -I is given in argument to the program. If this option is not present, only the entry name of the
  current directory is displayed.
```c++
int ls_dir(char * dirname, int option) {
    if (option) {
        execl("/bin/ls", "ls", "-l", dirname, NULL);
        exit(EXIT_SUCCESS);
    }
    else if (!option) {
        execl("/bin/ls", "ls", dirname, NULL);
        exit(EXIT_SUCCESS);
    }
    //See man 3 execl (path is the command to run, the rest are arguments to parse in, need to end with NULL
    exit(EXIT_FAILURE);
}
```
* Modify your code in order to display detailed information the entries of the current directory
if the option -I is given in argument to the program. If this option is not present, only the entry name of the
current directory is displayed.

* Documentation: getopt(1)

```c++
int main(int argc, char* argv[]){
    int c;                     //To read the option
    int lflag = 0;
    char* nomprog = argv[0];

    //If there is an option
    while ((c=getopt(argc,argv,"l")) != -1) {
        switch (c) {
            case 'l':
                lflag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l]\n", nomprog);
                exit(EXIT_FAILURE);
        }
    }

    return ls_dir(getenv("HOME"), lflag);
}
```

### Q3.5)
```c++
int main(int argc, char* argv[]){
    int opt;                     //To read the option
    int lflag = 0;
    char* nomprog = argv[0];

    //If there is an option
    while ((opt=getopt(argc,argv,"l")) != -1) {
        switch (opt) {
            case 'l':
                lflag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l] [dir]\n", nomprog);
                exit(EXIT_FAILURE);
        }
    }
    //optind holds the index of the first non-option argument in argv
    //so optind=1 if no arguments
    //If the command only has ./main -l
    char * dir = NULL;
    if (optind < argc) {
        dir = argv[optind];
    }
    return ls_dir(dir, lflag);
}
```

### Q3.6)
We now want to handle several directory names as arguments. Propose a solution handling several names in
argument to the program using Is_dir function.
```c++
int main(int argc, char* argv[]){
    int opt;                     //To read the option
    int lflag = 0;
    char* nomprog = argv[0];

    //If there is an option
    while ((opt=getopt(argc,argv,"l")) != -1) {
        switch (opt) {
            case 'l':
                lflag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l] [dir]\n", nomprog);
                exit(EXIT_FAILURE);
        }
    }
    //optind holds the index of the first non-option argument in argv
    //so optind=1 if no arguments

    char * dir = NULL;
    if (argc - optind > 1) {
        printf("Multiple directories are detected. Forking... \n");
        for (int i = optind; i < argc; i++) {
            char* current_dir = argv[i];
            printf("Directory %d : %s\n", i, current_dir);
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork failed \n");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0) {
                ls_dir(current_dir, lflag);
            } else {
                // Parent: wait for child to finish before continuing
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status)) {
                    printf("Finished listing %s (exit %d)\n", current_dir, WEXITSTATUS(status));
                    //if the child exit normally, print the exit code
                } else if (WIFSIGNALED(status)) {
                    printf("Listing %s terminated by signal %d\n", current_dir, WTERMSIG(status));
                    //if the child is killed by a signal (e.g., SIGKILL, SIGSEGV, etc).
                    // cf kill(2) since this kill is in fact an umbrella term for many types of kill, not just suspend 
                    //the process
                }
            }
        }
        printf("Finish listing for all \n");
        exit(EXIT_SUCCESS);
    }
    return ls_dir(dir, lflag);
}
```

**Explaination** : 
* After forking, a parallele pair of parent/children will run at the same time, consequently that 
parent will make more babies afterward if we don't wait (Only a parent process can wait)
* Here we are trying to stop the parent from going on if its parallele children is still running (by using pid != 0), 
we can look for them
* `status` is an integer variable that holds information about how a child process terminated.
* By writing `waitpid(pid, &status, 0);`, this function will write in status integer (which was at first NULL)


