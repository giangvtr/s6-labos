#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

    int pid;
    int child;
    int status;

    if (argc != 2){
        printf(" usage : %s binary_filename \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid=fork();
    switch (pid){
        case 0 :
            printf("PID %d : running a new program : %s\n", (int)getpid(), argv[1]);
            execl(argv[1], argv[1], (char *)0);
            /*Should never go there since exec changes the binary code to be run*/
            printf(" PID %d : exec failed\n", (int) getpid());
            exit (EXIT_FAILURE);
        case -1 :
            printf("Fork failed\n");
            exit (EXIT_FAILURE) ;
        default :
            child=wait (&status);
            printf("PID = %d : child process %d is finished, its status was %0x\n", (int)getpid(), child, status);
            exit(EXIT_SUCCESS);
    }
}
