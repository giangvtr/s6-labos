#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]){

    int pid;
    int child;
    int status;

    printf("Current PID process before the fork call: %d \n",(int)getpid());
    pid=fork();

    switch (pid){
        case 0 :
            printf("Child process : PID = %d, PPID = %d\n",(int)getpid(),(int)getppid());
            break;
        case -1 :
            printf("Fork failed\n");
            exit (EXIT_FAILURE) ;
        default :
            printf("Parent process : PID = %d, PPID = %d\n",(int)getpid(),(int)getppid());
            child=wait (&status);
            printf("Child process %d is finished, its status was %0x\n", child,status);
    }

    exit(EXIT_SUCCESS);
}
