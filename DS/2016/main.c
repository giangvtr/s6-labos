//
// Created by giangvu on 5/31/25.
//
#include <sys/wait.h>
#include "myls.h"

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
                exit(EXIT_SUCCESS);
            } else {
                // Parent: wait for child to finish before continuing
                int status;
                waitpid(pid, &status, 0);
            }
        }
        printf("Finish listing for all \n");
        exit(EXIT_SUCCESS);
    }
    return ls_dir(dir, lflag);
}