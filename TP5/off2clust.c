//
// Created by giangvu on 5/27/25.
//
#include "libfatutils.h"

/* Question 5: grep -aob '<[^>]\+>' image.fat | cut -d ":" -f 1 | ./off2clust
*/

int main(void) {
    char *line = NULL;            //Line read
    ssize_t nread = 0;            //Length of line retrieved

    //getline will allocate memory for line as needed.
    while((getline(&line, &nread, stdin)) != -1){
        //1. The string to convert (e.g., your input line)
        //2. Dont care about end caracter
        //3. Numerical base, 10 for decimal, 16 for hex, 0 for automatic mode
        unsigned long int offset = strtoul(line, NULL, 0);
        printf("This offset found in cluster : %lu\n", offset_to_cluster(offset));
    }

    return 0;
}
