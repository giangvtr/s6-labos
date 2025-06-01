//
// Created by giangvu on 5/31/25.
//

#ifndef PROCESS_DIR_H
#define PROCESS_DIR_H
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <locale.h>
#include "my_concat.h"


int read_dirQ1(const char * dir_name);
int read_dirQ3(const char * dir_name, const int aflag);
int read_dirQ5(const char * dir_name, const int aflag);
int read_dirQ7(char * dir_name, int aflag);

#endif //PROCESS_DIR_H
