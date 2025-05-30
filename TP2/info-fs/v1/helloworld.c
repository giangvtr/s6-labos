/*
// Created by mpressig on 26/01/2022.
*/

#include "helloworld.h"
#include <stdio.h>
#include <unistd.h>

int helloWorld() {
    dprintf(STDOUT_FILENO,"Hello, World!\n");
    return 0;
}
