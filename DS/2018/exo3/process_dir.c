//
// Created by giangvu on 5/31/25.
//


#include "process_dir.h"

int read_dirQ1(const char * dir_name) {
    struct dirent *ent;
    DIR *dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    exit(EXIT_SUCCESS);
}

int read_dirQ3(const char * dir_name, const int aflag) {
    struct dirent *ent;
    DIR * dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    if (strcmp(dir_name, ".") != 0) {
        printf("%s :\n", dir_name);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (!aflag && ent->d_name[0] == '.') {
            continue; //Skip hidden files
        }
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}

int read_dirQ5(const char * dir_name, const int aflag) {
    struct dirent *ent;
    DIR * dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    if (strcmp(dir_name, ".") != 0) {
        printf("%s :\n", dir_name);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (!aflag && ent->d_name[0] == '.') {
            continue; //Skip hidden files
        }
        if (ent->d_type == DT_DIR) {
            printf("\033[1m%s\033[0m\n", ent->d_name);
            continue;
        }
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}

int read_dirQ7(char * dir_name, int aflag) {
    //Dont forget to free the char* returned by my_concat
    struct dirent *ent;
    DIR * dir = opendir(dir_name);
    if (dir == NULL) {
        perror("Open file failed");
        exit(EXIT_FAILURE);
    }
    if (strcmp(dir_name, ".") != 0) {
        printf("%s :\n", dir_name);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (!aflag && ent->d_name[0] == '.') {
            continue; //Skip hidden files
        }

        //Bold if it is a directory (see readdir(3))
        if (ent->d_type == DT_DIR) {
            printf("\033[1m%s\033[0m\n", ent->d_name);
            continue;
        }

        //In blue if it is a file and user has the right to execute it (I made it up -
        //but the spirit here is to use stat structure to get user's right)
        if (ent->d_type == DT_REG) {
            //Inspire by example code in stat(2)
            struct stat sb;
            char * file_name = my_concat(dir_name, ent->d_name);
            printf("Looking at %s \n", file_name);
            if (file_name == NULL) {
                perror("Concat file name failed");
                exit(EXIT_FAILURE);
            }
            if (lstat(file_name, &sb) == -1) {
                perror("lstat");
                free(file_name);
                continue;
            }
            if (sb.st_mode & S_IXUSR) {
                //Use bit-wise operation & since st_mode is a large register with many bits adjacent
                printf("\033[34m%s\033[0m\n", ent->d_name);
                free(file_name);
                continue;
            }
        }
        printf("%s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}

