#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
    DIR* ptdir;
    struct dirent* entry;
    ptdir=opendir(".");
    if (NULL == ptdir)
    {
        fprintf(stderr, "Error with opendir \n");
        exit(1);
    }

    while((entry=readdir(ptdir))!= NULL)
    {
        printf("%s ", entry->d_name);

    }
    printf("\n");

    closedir(ptdir);

    return(0);


}
