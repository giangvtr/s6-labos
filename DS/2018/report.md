# DSTP-OS-2018

## Exercise 1 : grep (4 points)
### Q1.1) 
**Question:** Use grep that writes in a file list_date.txt the list of
the birth dates stored in datagen.txt . You do not have to remove duplicate values.

**Answer**:
  * Use flags `-o` for returns only matching fields, and `-E`(majuscule), which is obligated to every use
  * `grep -Eo "[0-9]{2}-[0-9]{2}-[0-9]{4}" datagen.txt`

### Q1.2)
Write in your report the command based on the use of grep and cut to retrieve the list of the year values
in the birth dates stored in this file. You do not have to remove duplicate values.

**Answer:**
* We can use `cut -d '<delimiter>' -f <field_number> <file>` to get date of birth field, 
that gives `cut -d ";" -f 2 datagen.txt`
* Pipelined with grep, we have `cut -d ";" -f 2 datagen.txt | grep -Eo "[0-9]{4}"`

### Q1.3)
Write in your report the command based on the use of `grep`, `uniq`, `cut` and `sort` to count the number of
people born each year in the file datagen.txt. For example, the output may look like this :
```c++
37 2000
52 2001
64 2002
```

**Answer**:
* We could use `sort -u` to replace the use of `uniq` : `cut -d ";" -f 2 datagen.txt | grep -Eo "[0-9]{4}" | sort -u`
* If stuck, type `sort --help` for manual
* Finally we have, `cut -d ";" -f 2 datagen.txt | grep -Eo "[0-9]{4}" | sort | uniq -c`

## Exercise 3 :
### Q3.1)
Similarly to a variable of type FILE* that handles a file, a variable of type DIR* enables to handle a directory. A basic ls is
provided in my_ls.c to list the entries of the current directory. Study it to implement a function myread_dir that takes a
directory name as an argument, reads the content of the directory and display it. It returns 1 if everything is ok, 0 otherwise.
Modify the my_ls program in order to call it on the current directory. Here is the prototype of the function :

**Answer:**
```c++
int read_dirQ1(char * dir_name) {
    DIR *dir;
    struct dirent *ent;
    dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    exit(EXIT_SUCCESS);
}

int main()
{
    return read_dirQ1(".");
}
```

### Q3.2)
Put this function `myread_dirQ1` in a file named `process_dir.c`. Create the appropriate
`process_dir.h`. Modify your `my_ls.c` if necessary.
Write a Makefile that :
- manages the compilation and linking of the related files as learnt during the labs.
- builds the program `my_ls`
- provides the rule *clean* that removes every binary file in the current directory

When taping make, it should build the my_ls program.
```makefile
CC= gcc
CFLAGS=-Wall -Wextra -MMD      # -fPIC: position-independent code (for shared lib)

TARGETS=my_ls         			   # Executables

all: $(TARGET_LIB) $(TARGETS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rules for the final target program
$(TARGETS): my_ls.o process_dir.o
	$(CC) $^ -o $@

clean:
	rm -f *.o *.d $(TARGETS)

-include $(wildcard *.d)

.PHONY: all clean
```

### Q3.3) 
Write in process_dir.c a function myread_dirQ3 whose prototype is :
`int read_dirQ3(char * dir_name, int aflag);`

Modify the my_ls program in order to enable the option "-a". If present, the program should display all files, even the hidden
ones. Otherwise, by default, my_ls does not display the hidden files/directories.

If dir_name is not ".", print the directory name before listing the files inside.

```c++
int read_dirQ3(const char * dir_name, const int aflag) {
    struct dirent *ent;
    DIR * dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    if (strcmp(dir_name, ".") != 0) {
        printf("%s :\n", dir_name);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (!aflag && ent->d_name[0] == '.') {
            continue; //Skip hidden files
        }
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}

```

```c++
#include <unistd.h>
#include "process_dir.h"

int main(int argc, char* argv[]) {
    int opt;                     //To read the option
    int aflag = 0;
    char* nomprog = argv[0];

    //If there is an option
    while ((opt=getopt(argc,argv,"a")) != -1) {
        switch (opt) {
            case 'a':
                aflag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] [dir]\n", nomprog);
                exit(EXIT_FAILURE);
        }
    }
    if (optind == argc) {
        read_dirQ3(".", aflag);
        exit(EXIT_SUCCESS);
    } else if (optind < argc) {
        for (int i = optind; i < argc; i++) {
            read_dirQ3(argv[i], aflag);
        }
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}
```

* Was debugging an error for half an hour. So it was changing `#include <bits/getopt_core.h>` to `#include <unistd.h>`

### Q3.4) Using manual
* `console_codes(4)`, `ascii (7)`. Cf. TP1 for using manual, search in manual
* In order to display an int in bold and in blue, we can use for example:
`printf("\033[34m\033[1m%d\033[0m ", 1);`

Could you explain :
- what does `\033` mean : ESC (this number is in octa (base 8))
    - Ssearch for ESC by typing `/ESC`, hit `n` several times
    - We'll get to `ESC (0x1B, ^[) starts an escape sequence`, which equals to 27 (base 10) and 33 (base 8)
- what does `\033[` mean : ESC [ - to starts an escape sequence, anything that is surrounded by `\033[ ... m` will be a 
text settings
- what does `\033[34m` mean ESC ["set blue foreground"] (can search by typing `/34`)
- what does `\033[1m` mean ESC ["set bold"]
- what does `\033[0m` mean ESC ["Reset"]

> Understand `man 4 console_codes` : 
>- The Most Common Sequence: `ESC [ ... m` (or `\033[...m` in C) sets text attributes like color and bold. 
>The numbers inside the brackets are parameters that mean different things. 
>- Common Parameters (search by typing the number itself)
>    - 0 = Reset all attributes (back to normal)
>    - 1 = Bold 
>    - 4 = Underline 
>    - 30–37 = Set text color (30=black, 31=red, 32=green, ..., 34=blue, ..., 37=white)
>    - 40–47 = Set background color (same color codes as above, but for background)

### Q3.5) Read_dirQ5 : 
Read the man page of readdir(3) to see how to check if the entry is a directory or not.
Write in process_dir.c a function myread_dirQ5 whose prototype is :
`int read_dirQ5(char * dir_name, int aflag);`

It works similarly to myread_dirQ3 with the following change:
> - when listing the content of a directory, if the current entry is a directory, its name is displayed in bold

```c++
int read_dirQ5(const char * dir_name, const int aflag) {
    struct dirent *ent;
    DIR * dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    if (strcmp(dir_name, ".") != 0) {
        printf("%s :\n", dir_name);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (!aflag && ent->d_name[0] == '.') {
            continue; //Skip hidden files
        }
        if (ent->d_type == DT_DIR) {
            printf("\033[1m%s\033[0m\n", ent->d_name);
            continue;
        }
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}
```

### Q3.6)
Read the man page of stat(2) to see how to get the rights of the owner, the group of the owner or the others.

Write in your report the name of the field in the stat structure containing this information.

> Type `man 2 stat`, go to section `The stat structure`, which will direct us to go to stat(3)
> Type `man 3 stat`, we'll find this at very first glance

```c++
struct stat {
           dev_t      st_dev;      /* ID of device containing file */
           ino_t      st_ino;      /* Inode number */
           mode_t     st_mode;     /* File type and mode */
           nlink_t    st_nlink;    /* Number of hard links */
           uid_t      st_uid;      /* User ID of owner */
           gid_t      st_gid;      /* Group ID of owner */
           dev_t      st_rdev;     /* Device ID (if special file) */
           off_t      st_size;     /* Total size, in bytes */
           blksize_t  st_blksize;  /* Block size for filesystem I/O */
           blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated */

           /* Since POSIX.1-2008, this structure supports nanosecond
              precision for the following timestamp fields.
              For the details before POSIX.1-2008, see VERSIONS. */

           struct timespec  st_atim;  /* Time of last access */
           struct timespec  st_mtim;  /* Time of last modification */
           struct timespec  st_ctim;  /* Time of last status change */

       #define st_atime  st_atim.tv_sec  /* Backward compatibility */
       #define st_mtime  st_mtim.tv_sec
       #define st_ctime  st_ctim.tv_sec
};
```
> * Look at the description of each attributes, we spot `st_mode` has potential, which direct us to inode(7)
> * In section `File type and mode` of inode(7), we'll find:
```c++
 S_IRWXU     00700   owner has read, write, and execute permission
 S_IRUSR     00400   owner has read permission
 S_IWUSR     00200   owner has write permission
 S_IXUSR     00100   owner has execute permission

 S_IRWXG     00070   group has read, write, and execute permission
 S_IRGRP     00040   group has read permission
 S_IWGRP     00020   group has write permission
 S_IXGRP     00010   group has execute permission

 S_IRWXO     00007   others (not in group) have read, write, and ex‐
                     ecute permission
 S_IROTH     00004   others have read permission
 S_IWOTH     00002   others have write permission
 S_IXOTH     00001   others have execute permission
```
**Answer**: Attribute `st_mode`

### Q3.7)
Write in process_dir.c a function `read_dirQ7` whose prototype is :
`int read_dirQ7(char * dir_name, int aflag);`

It works similarly to `read_dirQ5` with the following change:
- When listing the content of a directory, if the current entry is a file and if the owner has the right to 

To help you, we have provided in `my_concat.c/.h` a function that builds the absolute name of a file from its directory name and
its filename. For example, my_concat("~/Documents","the shape_of_water.mpg") returns
"~/Documents/the_shape_of_water.mpg". 

As it performs dynamic memory allocation for the resulting string, do not forget to free
it.

```c++
int read_dirQ7(char * dir_name, int aflag) {
    //Dont forget to free the char* returned by my_concat
    struct dirent *ent;
    DIR * dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    if (strcmp(dir_name, ".") != 0) {
        printf("%s :\n", dir_name);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (!aflag && ent->d_name[0] == '.') {
            continue; //Skip hidden files
        }

        //Bold if it is a directory (see readdir(3))
        if (ent->d_type == DT_DIR) {
            printf("\033[1m%s\033[0m\n", ent->d_name);
            continue;
        }

        //In blue if it is a file and user has the right to execute it (I made it up -
        //but the spirit here is to use stat structure to get user's right)
        if (ent->d_type == DT_REG) {
            //Inspire by example code in stat(2)
            struct stat sb;
            char * file_name = my_concat(dir_name, ent->d_name);
            printf("Looking at %s \n", file_name);
            if (file_name == NULL) {
                perror("Concat file name failed");
                exit(EXIT_FAILURE);
            }
            if (lstat(file_name, &sb) == -1) {
                perror("lstat");
                free(file_name);
                continue;
            }
            if (sb.st_mode & S_IXUSR) {
                //Use bit-wise operation & since st_mode is a large register with many bits adjacent
                printf("\033[34m%s\033[0m\n", ent->d_name);
                free(file_name);
                continue;
            }
        }
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}
```

Test your function. Modify your Makefile if necessary.

### Q3.8) Makefile static library
Modify your Makefile to add/modify the following rules:
* builds a static library named `libmyprocessdir.a` containing the files `process_dir.o` and `my_concat.o`
* provides a rule install that builds the library and installs properly the library in /usr/local/lib
* provides a rule distclean that removes properly every binary file build by the Makefile
* builds the program my_ls using this library

```makefile
CC= gcc
CFLAGS=-Wall -Wextra -MMD      # -fPIC: position-independent code (for shared lib)
LDFLAGS=-static
LDFLAGS  = -static             # Linker flags: force static linking
AR       = ar                  # Archiver tool to build static libraries
ARFLAGS  = -rv

TARGETS=my_ls         			   # Executables
LIBNAME     = libmyprocessdir.a           # Static library output
LIBOBJECTS  = process_dir.o my_concat.o    # Object files for the static library

INSTALL_LIB_PATH = /usr/local/lib

all: $(TARGETS) $(LIBNAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

#Equivalent: ar -rv libmyutil.a myfunc.o mytools.o
$(LIBNAME): $(LIBOBJECTS)
	$(AR) $(ARFLAGS) $@ $^

# Rules for the final target program
$(TARGETS): my_ls.o $(LIBNAME)
	$(CC) $(LDFLAGS) $^ -o $@

install: $(LIBNAME)
	sudo cp -f $(LIBNAME) $(INSTALL_LIB_PATH)
	sudo ldconfig

clean:
	rm -f *.o *.d $(TARGETS) $(LIBNAME)

distclean: clean
	sudo rm -f $(INSTALL_LIB_PATH)/$(LIBNAME)

-include $(wildcard *.d)

.PHONY: all clean distclean install

```