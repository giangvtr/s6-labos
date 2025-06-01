//
// Created by giangvu on 6/1/25.
//

#include "print_file.h"

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

