# TP4 : La commande wc
---

### Question 1 : Tester la commande wc

* **Tâches :** Tester la commande `wc` sur un fichier pour comprendre son comportement par défaut.

### Question 2 : Trouver la définition du descripteur standard

* **Tâches :** Utiliser `grep` pour trouver la définition du descripteur de fichier standard dans le fichier d'en-tête `<unistd.h>`.
* **Fonctions / Commandes à utiliser :**
    * `grep(1)`
    * `ls(1)` (potentiellement pour trouver le chemin de `/usr/include`).

### Question 3 : Compter les octets de l'entrée standard

* **Tâches :** Écrire un programme C `my_wc` qui lit l'entrée standard et affiche le nombre total d'octets lus, en utilisant une fonction `countByte(int fd)`.
* **Notions abordées :**
    * Programmation en C et la fonction `main` (CM5).
    * Lecture à partir d'un descripteur de fichier (`read`) (CM5).
    * Entrée standard (`stdin`) et son descripteur (0) (Lab 2, CM2, CM5).
    * Affichage formaté (`printf`) (CM5).
* **Fonctions / Commandes à utiliser :**
    * `read(2)`
    * `printf(3)`
    * Fichier d'en-tête `<unistd.h>`.
    * `echo(1)` (pour tester avec une entrée pipe).

### Question 4 : Écrire un Makefile de base

* **Tâches :** Créer un `Makefile` avec les règles `my_wc` (compilation), `clean` (suppression des fichiers binaires) et `all` (règle par défaut).
* **Fonctions / Commandes à utiliser :**
    * `make(1)`
    * `gcc(1)`
    * `rm(1)`

### Question 5 : Gérer les fichiers en entrée

* **Tâches :** Modifier le programme pour qu'il accepte des noms de fichiers en argument et compte les octets de chaque fichier, ou de l'entrée standard si aucun fichier n'est donné. Afficher le nom du fichier pour chaque résultat.
* **Notions abordées :**
    * Arguments de la ligne de commande (`argc`, `argv`) (CM5).
    * Gestion conditionnelle (boucles, if) pour traiter plusieurs fichiers ou l'entrée standard.
    * Ouverture et fermeture de fichiers spécifiques (`open`, `close`) (CM5).
    * Lecture à partir de différents descripteurs de fichiers (ceux obtenus par `open`) (CM5).
* **Fonctions / Commandes à utiliser :**
    * `open(2)`
    * `close(2)`
    * `read(2)`
    * `printf(3)`

### Question 6 : Ajouter la gestion des erreurs

* **Tâches :** Ajouter la gestion des erreurs (fichier non trouvable, permissions) et afficher les messages d'erreur sur la sortie d'erreur standard (`stderr`) en utilisant `errno` et `strerror`. Le programme doit imiter `wc -c`.
* **Notions abordées :**
    * Gestion des erreurs système en C (`errno`, `strerror`) (CM5).
    * Sortie d'erreur standard (`stderr`) (CM2, CM5).
    * Affichage sur stderr (`fprintf`) (CM5).
    * Permissions de fichiers (pour générer des erreurs de permission) (Lab 2, CM3).
* **Fonctions / Commandes à utiliser :**
    * `errno(3)`
    * `strerror(3)`
    * `fprintf(3)`

### Question 7 : Parallélisation avec processus

* **Tâches :** Ajouter une option `-f` pour que le traitement de chaque fichier soit effectué par un processus enfant distinct, permettant une exécution potentiellement simultanée (parallèle ou concurrente selon le nombre de cœurs).
* **Notions abordées :**
    * Parsing des options de ligne de commande avec `getopt` (CM5).
    * Création de nouveaux processus (`fork`) (Lab 3, CM4).
    * Attente de la fin des processus enfants (`wait`) (Lab 3, CM4).
    * Exécution simultanée de code (parallélisme/concurrence) (CM4).
* **Fonctions / Commandes à utiliser :**
    * `getopt(3)` (Note: La source liste `getopt(1)`, mais c'est la fonction C qui est pertinente ici)
    * `fork(2)`
    * `wait(2)`

### Question 8 : Installation du programme

- **Tâches :**  
  Modifier le Makefile pour ajouter les règles `install` (copie de l'exécutable dans `/usr/local/bin`) et `distclean` (suppression de l'exécutable installé), nécessitant les privilèges root.

- **Fonctions / Commandes à utiliser :**  
  - `cp(1)`  
  - `rm(1)`  
  - `sudo(8)`

---

### Question 9 : Ajouter l'option de comptage de lignes

- **Tâches :**  
  Ajouter une option `-l` pour compter les lignes au lieu des octets, en créant une nouvelle fonction `countLine(int fd)`. Le programme doit imiter `wc -l`.

- **Notions abordées :**  
  - Gestion d'options multiples avec `getopt` (CM5).  
  - Logique conditionnelle pour choisir la fonction de comptage (`countByte` ou `countLine`).  
  - Comptage de lignes (lecture de caractères ou de blocs, recherche du caractère newline `\n`).

- **Fonctions / Commandes à utiliser :**  
  - `getopt(3)`  
  - `read(2)` (pour lire le contenu du fichier/stream)

---

### Question 10 : Utilisation d'une variable d'environnement

- **Tâches :**  
  Modifier l'affichage pour colorer les nombres (bytes ou lignes) en rouge si la variable d'environnement `MY_WC_COLOR` a la valeur `"yes"`.

- **Notions abordées :**  
  - Variables d'environnement et leur accès en C (`getenv`, `environ`) (Lab 1, CM2, CM5).  
  - Codes de console ANSI pour la coloration du texte dans le terminal.  

- **Fonctions / Commandes à utiliser :**  
  - `getenv(3)`  
  - `environ(7)` (la variable globale)  
  - `console_codes(4)` (manuel décrivant les codes)  
  - `ascii(7)` (manuel décrivant les caractères ASCII)
