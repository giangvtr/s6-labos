**TP1 : Linux et Scripts**
---

### 1. Introduction au Shell (CM2)
*   **Fonctions/Commandes utilisées :**
    *   `ls(1)` : Lister le contenu d'un répertoire.
    *   `cd(1)` : Changer de répertoire.
    *   `pwd(1)` : Afficher le répertoire courant.
    *   `passwd(1)` : Changer le mot de passe.
    *   `gedit` : Éditeur de texte graphique (externe, pas de section man dans les sources).
    *   `nano` : Éditeur de texte console (externe, pas de section man dans les sources).
    *   `cat(1)` : Afficher le contenu d'un fichier.
    *   `&` : Lancer une commande en arrière-plan (shell feature).
    *   `gcc` : Compileur C (externe, pas de section man dans les sources).
    *   `./nom_programme` : Exécuter un programme du répertoire courant.

---

### 2. Documentation et Manual
*   **Notions abordées (cf. CM2 - Documentation des commandes) :**
    *   Utilisation de l'option `--help` pour obtenir de l'aide ainsi que des pages de manuel (`man`).
    *   Structure des pages `man` : SYNOPSIS, DESCRIPTION, RETURN VALUE, ERRORS.
    *   Sections numérotées des pages `man` (commandes, appels système, sous-routines C, etc.). Trouver une page spécifique avec la section (`man 2 stat`).
    *   Navigation et recherche dans une page `man` (`/`- search forward, `?` - search backward, `n`-jump to next match), `p`).
    *   Productivité en console : historique des commandes (flèches, Ctrl+R), complétion par tabulation (`Tab`), copier/coller (double/triple/middle click).
    *   Gestion des caractères spéciaux dans les noms de fichiers, notamment les espaces, à l'aide de guillemets (`"`).
    *   Interruption (`Ctrl+C`), suspension (`Ctrl+Z`) et reprise (`fg`, `bg`) de processus en console.
    *   Le code de retour d'une commande (`$?`) et l'enchaînement conditionnel (`&&`, `||`) sont abordés dans le **CM2**.
*   **Fonctions/Commandes utilisées :**
    *   `man(1)` : Afficher les pages de manuel.
    *   `stat(1)` : Afficher les informations de statut d'un fichier (utilisé dans Lab 2, mais pertinent pour la documentation de `stat(2)`).
    *   `stat(2)` : Appel système pour obtenir des informations sur un fichier (documenté via `man 2 stat`).
    *   `--help` : Option générique de commande.
    *   `history` : Afficher l'historique des commandes (shell builtin).
    *   `fg` : Ramener un processus en arrière-plan en avant-plan (shell builtin).
    *   `bg` : Lancer un processus en arrière-plan (shell builtin).

---

### 3. Navigation et Manipulation du Filesystem

*   **Notions abordées (cf. CM3 - Introduction au Filesystem) :**
    * Structure du système de fichiers Linux : Arborescence hiérarchique avec répertoire racine /, dossiers standards (/home, /etc, /dev, /proc, /sys, etc.). Répertoire home (~) et fichiers/répertoires cachés (commençant par .).
    * Commandes de gestion de fichiers : mkdir, rm, cp, mv, touch (+ option -r pour opérations récursives).
    * Différence entre suppression console (rm) et via explorateur (corbeille).
    * Permissions et superutilisateur : Notion de root, utilisation de sudo (fichier /etc/sudoers), gestion des droits (rwx), chown, chmod.
    * Système unifié de fichiers : Tout est fichier, y compris les périphériques et les infos du noyau.
      
*   **Fonctions/Commandes utilisées :**
    *   `cd(1)` : Changer de répertoire.
    *   `pwd(1)` : Afficher le répertoire courant.
    *   `ls(1)` : Lister le contenu d'un répertoire. Option `-a` (all), `-l` (long format).
    *   `mkdir(1)` : Créer un répertoire.
    *   `rm(1)` : Supprimer fichier/répertoire. Option `-r` (recursive).
    *   `cp(1)` : Copier fichier/répertoire. Option `-r` (recursive).
    *   `mv(1)` : Déplacer/renommer fichier/répertoire.
    *   `touch(1)` : Créer un fichier vide.
    *   `sudo(8)` : Exécuter une commande en tant que superutilisateur.
    *   `apt-get` : Gérer les paquets logiciels (externe, pas de section man).

---

### 4. Expansion de Noms d'Entrées (Globbing)

*   **Notions abordées (cf. CM2 - Introduction au Shell):**
    *   Le concept d'une "entrée" dans un répertoire (fichier, répertoire, lien, etc.).
    *   L'expansion de noms d'entrée, ou "globbing", pour sélectionner des groupes d'entrées (*).
    *   Utilisation de métacaractères (ou jokers) pour définir des motifs génériques : `*` (n'importe quelle chaîne, même vide), `?` (un seul caractère), `[]` (un caractère parmi une liste/intervalle), `[!...]` (un caractère ne figurant pas dans la liste/intervalle).
    *   Combinaison de métacaractères.
    *   Désactivation du comportement spécial des métacaractères (échappement avec `\`, guillemets).
    *   La différence entre globbing et la recherche par contenu ou autres critères (`grep`, `find`) est mentionnée dans le **CM2**.
    
*   **Fonctions/Commandes utilisées :**
    *   Les métacaractères (`*`, `?`, `[`, `]`, `!`) sont utilisés comme arguments des commandes de manipulation de fichiers comme `ls(1)`, `rm(1)`, `cp(1)`, `mv(1)`, etc..

---

### 5. Scripts Bash – Résumé synthétique (cf. CM2 - Ecrire un script)
- **Création & exécution** :
  - Script = fichier texte contenant des commandes, commence par `#!/bin/bash` (shebang).
  - Exécution directe après `chmod +x script.sh` → `./script.sh`, ou indirecte → `bash script.sh`.

- **Variables & arguments** :
  - Déclaration : `VAR=valeur`, utilisation : `$VAR`.
  - Accès aux arguments : `$0` (nom du script), `$1`, `$2`, ..., `$#` (nb d’args), `$*` (liste), `$?` (code retour).
  - Variables d’environnement (`USER`, `PATH`, etc.), modification temporaire (`export VAR=...`) ou via `.bashrc`.

- **Entrées / sorties & structures de contrôle** :
  - Lecture : `read`, affichage : `echo`, `printf`.
  - Conditionnels : `if`, `elif`, `else` avec `[ ... ]` (tests sur chaînes, fichiers, nombres).
  - Boucles : `for`.
  - Enchaînements : `cmd1 && cmd2`, `cmd1 || cmd2`, `;` (séquentiel).
  - Redirections : `>`, `>>`, `2>`, `2>>`, `<`, `2>&1`. Descripteurs : `0` (stdin), `1` (stdout), `2` (stderr).
  - Pipes (`|`) pour chaîner les commandes.

- **Commandes utiles dans les scripts** :
  - `grep`, `egrep`, `wc`, `sort`, `uniq`, `wget`, `zcat`, `mv`, `cp`, `source`, `export`, `read`, `echo`, `printf`.
  - Answer: 
`wget -O - "$URL" | zcat | egrep -o '^\d+\.\d+\.\d+\.\d+\b|^([a-fA-F0-9]+\:){7}[a-fA-F0-9]+\b' | sort | uniq -c > frequency.log`


