# TP4 : La commande wc
---

### Question 1 : Tester la commande wc
`wc somefile.txt`
### Question 2 : Trouver la définition du descripteur standard
`grep STDIN_FILENO /usr/include/unistd.h`


### Question 3 : Compter les octets de l'entrée standard
```c++
#include <stdio.h>
#include <unistd.h>

int countByte(int fd) {
    int count = 0;
    char ch;
    while (read(fd, &ch, 1) != 0) {
        count++;
    }
    return count;
}

int main() {
    int nbbytes = countByte(STDIN_FILENO);
    printf("%d\n", nbbytes);
    return 0;
}
```

### Question 4 : Écrire un Makefile de base

* **Tâches :** Créer un `Makefile` avec les règles `my_wc` (compilation), `clean` (suppression des fichiers binaires) et `all` (règle par défaut).
* **Fonctions / Commandes à utiliser :**
    * `make(1)`
    * `gcc(1)`
    * `rm(1)`

### Question 5 : Count bytes from files or stdin
```c++
int main(int argc, char* argv[]) {
    if (argc == 1) {
        int nbbytes = countByte(STDIN_FILENO);
        printf("%d\n", nbbytes);
    } else {
        for (int i = 1; i < argc; ++i) {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                perror(argv[i]);
                continue;
            }
            int nbbytes = countByte(fd);
            printf("%d %s\n", nbbytes, argv[i]);
            close(fd);
        }
    }
    return 0;
}
```

### Question 6 : Error messages with `errno` and `strerror`

```c++
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* nomprog = argv[0];
    if (argc == 1) {
        int nbbytes = countByte(STDIN_FILENO);
        printf("%d\n", nbbytes);
    } else {
        for (int i = 1; i < argc; ++i) {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1) {
                fprintf(stderr, "%s: %s: %s\n", nomprog, argv[i], strerror(errno));
                continue;
            }
            int nbbytes = countByte(fd);
            printf("%d %s\n", nbbytes, argv[i]);
            close(fd);
        }
    }
    return 0;
}
```

### Question 7 : Option -f for parallel processing
```c++
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

void process_file(const char *fileName, const char *program) {
    int fd = open(fileName, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: %s: %s\n", program, fileName, strerror(errno));
        return;
    }
    int result = countByte(fd);
    printf("%d %s\n", result, fileName);
    close(fd);
}

int main(int argc, char* argv[]) {
    int c;
    int fflag = 0;
    char* nomprog = argv[0];

    while ((c = getopt(argc, argv, "f")) != -1) {
        switch (c) {
            case 'f':
                fflag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f] file...\n", nomprog);
                exit(EXIT_FAILURE);
        }
    }

    if (argc == optind) {
        int nbbytes = countByte(STDIN_FILENO);
        printf("%d\n", nbbytes);
        return 0;
    }

    if (!fflag) {
        for (int i = optind; i < argc; ++i)
            process_file(argv[i], nomprog);
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
                process_file(argv[i], nomprog);
                exit(EXIT_SUCCESS);
            } else {
                pids[j] = pid;
            }
        }
        for (int i = 0; i < num_files; ++i) {
            int status;
            waitpid(pids[i], &status, 0);
        }
        free(pids);
    }
    return 0;
}
```

### Question 8 : Full Makefile

- **Tâches :**  
  Modifier le Makefile pour ajouter les règles `install` (copie de l'exécutable dans `/usr/local/bin`) et `distclean` (suppression de l'exécutable installé), nécessitant les privilèges root.

- **Fonctions / Commandes à utiliser :**  
  - `cp(1)`  
  - `rm(1)`  
  - `sudo(8)`

---

### Question 9 : Option -l for line count
```c++
int countLine(int fd) {
    int count = 0;
    char ch;
    while (read(fd, &ch, 1) != 0) {
        if (ch == '\n') count++;
    }
    return count;
}
```

---

### Question 10 : Color output with MY_WC_COLOR
  Modifier l'affichage pour colorer les nombres (bytes ou lignes) en rouge si la variable d'environnement `MY_WC_COLOR` a la valeur `"yes"`.

- **Notions abordées :**  
  - Variables d'environnement et leur accès en C (`getenv`, `environ`) (Lab 1, CM2, CM5).

- **Fonctions / Commandes à utiliser :**  
  - `getenv(3)` : getenv("HOME") will return home directory path
  - `environ(7)` (la variable globale)  
  - `console_codes(4)` : Documents escape sequences used to control the Linux console, like changing colors, moving the cursor, clearing the screen, etc.
    Styling text (bold, underline, colors).
    Doing cursor movements in terminal UIs.
    Making output visually dynamic.  
  - `ascii(7)` (code ASCII)
> **How to understand console_codes(4)**:
>  * Most Common Sequence: `ESC [ ... m` or `\033[ ... m` to delimiter the border. The parameters inside can set text 
attributes like color and bold.
>  * Some meaning :
>    * 0 = Reset all attributes (back to normal)
>    * 1 = Bold 
>    * 4 = Underline 
>    * 30–37 = Set text color (30=black, 31=red, 32=green, ..., 34=blue, ..., 37=white)
>    * 40–47 = Set background color (same color codes as above, but for background)

