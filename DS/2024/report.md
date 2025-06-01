# DSTP-OS-2024

## Exo 1 : Linux commands (2 points)
For this exercise, we ask you to give the result in a single one command line, using input/output redirection(s) to
combine these commands with any relevant options : `cat`, `cut`, `echo`, `grep`, `head`, `ls`, `sort`, `uniq`, `wc`

The provided file 'NASA_access_log_Jul95_1000' stores the first 1000 log messages of the NASA web site during
august 1995. The logs are an ASCII file with one line per request, with the following columns:
1. host making the request. A hostname when possible, otherwise the Internet address could not be looked up.

2. timestamp in the format "DAY MON DD HH:MM:SS YYYY", where DAY is the day of the week, MON is the name
of the month, DD is the day of the month, HH:MM:SS is the time of day using a 24-hour clock. YYYY : year. The timezone is -0400.
3. request given in quotes. GET means that the request is a download and is followed by the resources to be
downloaded
4. HTTP reply code
5. bytes in the reply

### 1: Write in your report the command line that lists the downloaded jpg resources
Expected result for question 1 (only the first and last lines are shown):
```commandline
cut -f 4 NASA_access_log_Jul95_1000 | grep -E "\.jpg$"
/shuttle/missions/sts-71/images/KSC-95EC-0916.jpg

/shuttle/missions/sts-71/images/KSC-95EC-0613.jpg
/shuttLle/missions/sts-71/images /KSC-95EC-0882.jpg
```
**Note** : 
* `cut` default delimiter is a tab (for each column)
* " \ " in grep for literal string (.) 

### 2: Write in your report the command line that lists the line where the request is from United Kingdom (the name of the host making the requests ends with '.uk’)
```commandline
cut -f 1 NASA_access_log_Jul95_1000 | grep -E "\.uk$"
```

## Exo 2: Script (3 pts)
When looking for a file with the find command, one can use its time characteristics stored in its inode :
+ atime — access time = last time file opened
+ mtime — modified time = last time file contents was modified
+ ctime — changed time = last time file inode was modified

### Question 3: 
Look at the `find(1)` manpage to find what is the find option to test the last time the file content was modified in minutes. 
Write the answer in your report with the copy of the option description.

```
-mmin n       File's  data was last modified less than, more than or exactly n
              minutes ago.
+n     for greater than n,
-n     for less than n,
n      for exactly n.
```

### QUESTION 4: 
Write in your report the command that finds all entries in the current directories and its subdirectories
whose **content (need to use type -f ? )** has been modified since one minute. 

`find . type -f -mmin -1`

### : QUESTION 5: 
Write a script `script.sh` that displays all the files - **and only the file (need to use type -f)** - in the current directory and its subdirectories
whose content has been modified since last X minutes, X being given as the argument of the script
no argument is given, the script displays an error message on stderr.

> Rappel:
> * Before running, need to grant execution right to owner : `chmod +x myscript.sh`
> * Run the script by : `./myscript.sh 180` or `bash myscript.sh 180` or `sh myscript.sh 180`

```bash
#!/bin/bash
# Should have space between [ ]
if [ $# -ne 1 ]
  then
  echo "This program should have one argument" >&2
  exit 1
fi

# No spaces around =
MIN=$1
find . -type f -mmin -$MIN
```

## EXO 3 : FILE SYSTEM (2 pts)
The provided newfile is an ext2 filesystem. It contains a file named myfile.

### Question 6 : 
The size of myfile with the command used to find the answer:

**Answer** : 
* (Recommended) Simply type `ls -l` where the filesystem is. Read the 5th column, it is the file size in bytes.
* If the file system is mounted : `df -h mymountpoint`. The answer it gives could be smaller than real size since 
some space is used for filesystem metadata and reserved blocks.
* (For advanced use) If the FS is not mounted (just a file image) : `sudo dumpe2fs -h myfilesystem` or `echo "show_super_stats" | debugfs myfilesystem`. Then calculate: Block count × Block size = Total size


How to mount ?
```commandline
mkdir mymountpoint 
ls mymountpoint 
ls -l 
sudo mount -o loop myfilesystem mymountpoint 
ls -l
```

### Question 7: 
How many blocks indirections are required to store the content of myfile (no calculation is required)
Give the commands you use to get this information with a copy of the list of the blocks used to store the content
of this file.


```commandline
echo "stat /myfile" | sudo debugfs myfilesystem
# The answer is in section "BLOCKS": (0)
# Need to be in the directory where found filesystem

#equivalent 1
sudo debugfs -R "stat /myfile" myfilesystem             

# equivalent 2 
ls -i /mnt/newfile/myfile
sudo debugfs -R "blocks <inode_number>" myfilesystem

#equivalent 3
sudo debugfs -R "blocks $(ls -i /mymountpoint/myfilesystem/myfile | awk '{print $1}')" myfilesystem
```

Here is an example output
```commandline
Inode: 13   Type: regular    Mode:  0644   Flags: 0x0
Generation: 4075384924    Version: 0x00000000:00000004
User:     0   Group:     0   Project:     0   Size: 1087582
File ACL: 0
Links: 1   Blockcount: 2136
Fragment:  Address: 0    Number: 0    Size: 0
 ctime: 0x683c6905:4115ecdc -- Sun Jun  1 16:51:49 2025
 atime: 0x683c6905:405ed23c -- Sun Jun  1 16:51:49 2025
 mtime: 0x683c6905:4115ecdc -- Sun Jun  1 16:51:49 2025
crtime: 0x683c6905:405ed23c -- Sun Jun  1 16:51:49 2025
Size of extra inode fields: 32
BLOCKS:
(0-11):2048-2059, (IND):1037, (12-15):2060-2063, (16-63):1072-1119, (64-127):1152-1215, (128-255):1280-1407, (256-265):2688-2697
TOTAL: 267
```
**Remarks**: 
* In the BLOCKS List, we see (0-11), which is all direct blocks are used. 
* Then we see (IND), which means the single indirect blocks are used. 
* No (DIND) and (TIND) are used, so only one indirection is used to store this file

### Question 7 BIS:
Justify the previous answer by a few calculations in your report, from filesystem parameters.
Type in : 
* `echo "show_super_stats" | debugfs myfilesystem`. 
* Check the number of direct blocks. For example, if (0-11), this system has 16 blocks in total, so like in cours (N=16). 
But this number could change for other ext2 file system
* Read the Block size. Here is 4096 bytes / 4 bytes = 1024 pointers which means an indirect block could point to 1024 other blocks
* So in short :
  * 12 direct blocks : 12 * 4096 = 49152 bytes = 48 KiB (divise by 2^10)
  * 1 indirect block : 1024 * 4096 bytes = 4,194,304 bytes = 4 MB
  * 1 double indirect block : 1024^2 * 4096 = 4 GB
  * 1 triple block : 

So if file size falls between : 48 KiB < size < 4MB + 48 KiB --> single indirection is enough

## EXO 4: Command myhexdump in C + Makefile (11 pts)
Go to the repertory named myhexdump. There are two source code:
* `myhexdump.c` with a main function to be completed
* `print_file.c` with the printFile function to be completed

### Question 8: 
Write a Makefile to build the program

### Question 9: Function `printFile`
```c++
void printFile(int fd, int size, int flagASCII) {
    int count = 0;
    char ch;
    if (size == -1) size = INT_MAX;

    while (read(fd, &ch, 1) != 0 && count < size) {
        count++;
        switch (flagASCII) {
            case 0:
                printf("%c", ch);
                break;
            case 1:
                if ((count-1) % 2 == 0 && (count-1) > 0) {
                    printf(" ");
                }
                if ((count-1)%16 == 0 && count-1 > 0) {
                    printf("\n");
                }
                printf("%.2x", ch);
                break;
            default:
                perror("flagASCII");
                exit(EXIT_FAILURE);
        }
    }
}

```

### Question 10: Main takes file argument
```c++
int main(void) {
    int fd = open("some-file", O_RDONLY);
    if (fd == -1) {
        perror("some-file");
        exit(EXIT_FAILURE);
    }
    printFile(fd,34,1);
}
```

### Question 11: Arguments command line and options
Modify the main function such as it handles 2 options:
* -c to display file with ASCII values
* -n size to display the size first bytes of the file

If no filename is given as argument, it should display an error on stderr. If the filename
given as argument cannot be read, it should display the relevant error message.

Example of expected results (do not compare to the real hexdump command that handles little-endian display)
```c++
```

### Question 12: Bonus, swapping pairs to become little endian
```c++
void printFile(int fd, int size, int flagASCII) {
    int count = 0;
    unsigned char ch;
    unsigned char buf[2];
    int buf_pos = 0;
    if (size == -1) size = INT_MAX;

    while (read(fd, &ch, 1) != 0 && count < size) {
        buf[buf_pos++] = ch;
        if (buf_pos == 2) {
            // Swap the two bytes and print as hex
            if (flagASCII == 1) {
                printf("%02x%02x", buf[1], buf[0]); // Print as "4065" for "6540"
            }
            buf_pos = 0;
        }
        count++;
    }

    // If there's an odd byte left, print it alone (not swapped)
    if (buf_pos == 1 && flagASCII == 1) {
        printf("%02x", buf[0]);
    }
}
```