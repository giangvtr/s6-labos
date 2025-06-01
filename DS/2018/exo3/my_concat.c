#include "my_concat.h"
#include <stdlib.h>
#include <string.h>

char * my_concat(char * dir_name, char * filename)
{
    char *complete_name = (char * ) malloc(strlen(dir_name) +strlen(filename) +2);
    if(complete_name !=NULL)
    {
        strcpy(complete_name,dir_name);
        if(dir_name[strlen(dir_name)-1] != '/')
            complete_name[strlen(dir_name)] = '/';
        strcat(complete_name,filename);
    }
    return complete_name;
}



