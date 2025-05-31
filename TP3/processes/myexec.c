//
// Created by giangvu on 5/31/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_p1(void) {
    pid_t pid1 = getpid();
    sleep(2);
    for (int i = 0; i < 10; i++) {
        printf("%d : message %d \n", pid1, i+1);
    }
}

void run_p2(void) {
    char * argv_list[] = {"ls", "-l", ".", NULL};
    execvp("ls", argv_list);
    //Soit : execv("/bin/ls", argv_list);  avec chemin absolue de l'executable ls
}

int main() {
    printf("Hello ! \n");
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        run_p1();
        exit(EXIT_SUCCESS);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        run_p2();
        exit(EXIT_SUCCESS);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    printf("Bye !");
    exit(EXIT_SUCCESS);
}
