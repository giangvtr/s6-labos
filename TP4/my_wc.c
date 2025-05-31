#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>          //To use the errno variable
#include <stdlib.h>
#include <string.h>         //To show error message
#include <sys/wait.h>

/*
When -f is used, you should fork() before opening the file, and each child should process only one file.
The parent should wait for all children after launching them.
The countByte function should use char ch; (not char *ch;) and pass &ch to read().
Use wait() or waitpid() in the parent to collect all children.
*/

extern char **environ;

int countByte(int fd) {
    int count = 0;
    char ch;
    while (read(fd, &ch, 1) != 0) {
        count++;
    }
    return count;
}

int countLine(int fd) {
    int count = 0;
    char ch;
    while (read(fd, &ch, 1) != 0) {
        if (ch == '\n') count++;
    }
    return count;
}

int print_with_color(const char* color_env, int toPrint) {
    if (color_env == NULL) {
        return 0;
    }
    if (strcmp(color_env, "yes") == 0) {
        printf("\033[31m%d\033[0m", toPrint);
        return 1;
    }
    else if (strcmp(color_env, "no") == 0) {
        printf("%d", toPrint);
        return 1;
    }
    return 0;
}

void process_file(const char *fileName, int lflag, const char *color, const char *program) {
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: %s: %s\n", program, fileName, strerror(errno));
        return;
    }
    int result = lflag ? countLine(fd) : countByte(fd);
    print_with_color(color, result);
    printf(" %s\n", fileName);
    close(fd);
}

int main(int argc, char* argv[], char* envp[]) {
    int c;                     //To read the option
    int fflag = 0;
    int lflag = 0;
    char* nomprog = argv[0];

    char *color;
    color = getenv("MY_WC_COLOR");

    //If there is an option
    while ((c=getopt(argc,argv,"fl")) != -1) {
        switch (c) {
            case 'f':
                fflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f] file...\n", nomprog);
                exit(EXIT_FAILURE);
        }
    }

    //If dont use fflag
    if (argc == optind) {
        // Aucun nom de fichier, lire sur l'entrée standard
        if (lflag) {
            int nblines = countLine(STDIN_FILENO);
            print_with_color(color, nblines);
            printf("\n");
            return 0;
        } else {
            int nbbytes = countByte(STDIN_FILENO);
            print_with_color(color, nbbytes);
            printf("\n");
            return 0;
        }
    }

    //If an option f is given but no file name after it, then error
    if (fflag && argc <= optind ) {
        fprintf(stderr, "No argument provided \n");
        return 1;
    }

    // Sequential or parallel processing
    if (!fflag) {
        for (int i = optind; i < argc; ++i)
            process_file(argv[i], lflag, color, nomprog);
    } else {
        int num_files = argc - optind;
        pid_t *pids = malloc(num_files * sizeof(pid_t));
        if (!pids) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        int j = 0;
        for (int i = optind; i < argc; ++i, ++j) {
            pid_t pid = fork();
            if (pid == -1) {
                fprintf(stderr, "Fork failed\n");
                continue;
            }
            if (pid == 0) {
                process_file(argv[i], lflag, color, nomprog);
                exit(EXIT_SUCCESS);
            } else {
                pids[j] = pid;
            }
        }
        // Parent waits for all children
        for (int i = 0; i < num_files; ++i) {
            int status;
            waitpid(pids[i], &status, 0);
        }
        free(pids);
    }
    return 0;
}