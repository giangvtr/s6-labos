//
// Created by giangvu on 6/1/25.
//

#include <ctype.h>

#include "print_file.h"
#include <errno.h>
#include <fcntl.h>
#include <bits/fcntl-linux.h>

int main(int argc, char* argv[]) {
    int option;                     //To read the option
    int cflag = 0;
    char *nvalue = NULL;
    char* nomprog = argv[0];
    int size = -1;

    //If there is an option
    while ((option=getopt(argc,argv,"cn:")) != -1) {
        switch (option) {
            case 'c':
                cflag = 1;
                break;
            case 'n':
                nvalue = optarg;
                break;
            case '?':
                if (optopt == 'n') fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt)) fprintf(stderr, "Unknown option `%c'.\n", optopt);
                else fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                fprintf(stderr, "Usage: %s [-n size] [-c] filename\n", nomprog);
                abort();
        }
    }

    if (optind >= argc) {
        printf("Hello world! \n");
        fprintf(stderr, "Usage: %s [-n size] [-a] filename\n", nomprog);
        return 1;
    }

    if (nvalue) size = atoi(nvalue);
    char * fileName = argv[optind];
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printFile(fd,size,cflag);
    printf("\n");
}
