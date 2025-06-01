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
            read_dirQ7(argv[i], aflag);
        }
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}