#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main (int argc, char *argv[], char *envp[])
{
    char *home, *host;
    int i;

    home = getenv("HOME");
    host = getenv("HOSTNAME");

    printf ("Your home directory is %s on %s.\n", home, host);

    i=0;
    /*environ can be replaced by envp*/
    while(environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
    return EXIT_SUCCESS;
}
