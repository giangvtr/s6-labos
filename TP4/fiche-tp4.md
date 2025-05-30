# Fiche Détaillée - TP4 : La commande wc
---

### Question 1 : Tester la commande wc

* **Tâches :** Tester la commande `wc` sur un fichier pour comprendre son comportement par défaut.
* **Notions abordées :**
    * Utilisation de commandes de base sous Linux (Lab 1, CM2).
    * La commande `wc` et son usage.
* **Fonctions / Commandes à utiliser :**
    * `wc(1)`
* **Compétences spécifiques :** Exécuter une commande simple, observer et comprendre son comportement.

### Question 2 : Trouver la définition du descripteur standard

* **Tâches :** Utiliser `grep` pour trouver la définition du descripteur de fichier standard dans le fichier d'en-tête `<unistd.h>`.
* **Notions abordées :**
    * Recherche de texte dans des fichiers avec `grep` (Lab 1, Lab 5, TD 1, CM2).
    * Fichiers d'en-tête C (`.h`) et leur localisation (`/usr/include`).
    * Descripteurs de fichiers standard (stdin, stdout, stderr) (Lab 2, CM2, CM5).
* **Fonctions / Commandes à utiliser :**
    * `grep(1)`
    * `ls(1)` (potentiellement pour trouver le chemin de `/usr/include`).
* **Compétences spécifiques :** Utiliser `grep` efficacement pour la recherche, comprendre le rôle des descripteurs de fichiers standard.

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
* **Compétences spécifiques :** Écrire une fonction C simple pour lire un flux, utiliser `read` pour compter des octets.

### Question 4 : Écrire un Makefile de base

* **Tâches :** Créer un `Makefile` avec les règles `my_wc` (compilation), `clean` (suppression des fichiers binaires) et `all` (règle par défaut).
* **Notions abordées :**
    * Syntaxe et utilisation de `make` (Lab 3).
    * Règles classiques (`all`, `clean`) dans un Makefile (Lab 3).
    * Compilation avec `gcc` (Lab 1, Lab 4).
* **Fonctions / Commandes à utiliser :**
    * `make(1)`
    * `gcc(1)`
    * `rm(1)`
* **Compétences spécifiques :** Écrire un Makefile fonctionnel pour un projet C simple.

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
* **Compétences spécifiques :** Utiliser les arguments de `main`, manipuler plusieurs fichiers en C, gérer un cas par défaut (stdin).

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
    * `chmod(1)` (pour modifier les permissions de test)
* **Compétences spécifiques :** Implémenter une gestion d'erreur robuste, rediriger la sortie d'erreur.

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
* **Compétences spécifiques :** Programmation multiprocessus simple, gestion des options de programme complexes.

### Question 8 : Installation du programme

- **Tâches :**  
  Modifier le Makefile pour ajouter les règles `install` (copie de l'exécutable dans `/usr/local/bin`) et `distclean` (suppression de l'exécutable installé), nécessitant les privilèges root.

- **Notions abordées :**  
  - Règles `install` et `distclean` dans un Makefile (Lab 3).  
  - Copie et suppression de fichiers (`cp`, `rm`) (Lab 1, CM2, CM3).  
  - Hiérarchie du système de fichiers Linux (`/usr/local/bin`) (Lab 2, CM3).  
  - Privilèges root et utilisation de `sudo` pour l'installation (Lab 1, Lab 2, CM2, CM3).

- **Fonctions / Commandes à utiliser :**  
  - `cp(1)`  
  - `rm(1)`  
  - `sudo(8)`

- **Compétences spécifiques :**  
  Déployer un programme exécutable sur un système Linux selon les conventions, gérer les privilèges nécessaires.

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

- **Compétences spécifiques :**  
  Étendre les fonctionnalités d'un programme via options, implémenter une nouvelle logique de comptage.

---

### Question 10 : Utilisation d'une variable d'environnement

- **Tâches :**  
  Modifier l'affichage pour colorer les nombres (bytes ou lignes) en rouge si la variable d'environnement `MY_WC_COLOR` a la valeur `"yes"`.

- **Notions abordées :**  
  - Variables d'environnement et leur accès en C (`getenv`, `environ`) (Lab 1, CM2, CM5).  
  - Codes de console ANSI pour la coloration du texte dans le terminal.  
  - Manipulation de chaînes de caractères en C (comparaison).

- **Fonctions / Commandes à utiliser :**  
  - `getenv(3)`  
  - `environ(7)` (la variable globale)  
  - `console_codes(4)` (manuel décrivant les codes)  
  - `ascii(7)` (manuel décrivant les caractères ASCII)

- **Compétences spécifiques :**  
  Configurer un programme via l'environnement, réaliser un affichage coloré dans un terminal.
