//
// Created by giangvu on 5/31/25.
//
#include "myls.h"

int ls_dir(const char * dirname, int option) {
    const char *arg2 = dirname ? dirname : ".";

    if (option) {
        execl("/bin/ls", "ls", "-l", arg2, NULL);
        exit(EXIT_SUCCESS);
    }
    else if (!option) {
        execl("/bin/ls", "ls", arg2, NULL);
        exit(EXIT_SUCCESS);
    }
    //See man 3 execl (path is the command to run, the rest are arguments to parse in, need to end with NULL
    exit(EXIT_FAILURE);
}

