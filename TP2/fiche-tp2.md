# TP2 : Filesystem

Se familiariser avec un système de fichiers Linux, étudier Ext2, analyser la structure d’un inode.

---

## 1. Introduction & Permissions

### 🔸 Notions abordées
- Définition d’un File System (interface logicielle entre le stockage et l’organisation des données).
- Propriétés des fichiers et répertoires.
- Permissions (lecture `r`, écriture `w`, exécution `x`) — fichiers/répertoires.
- Modes de définition des permissions : symbolique (`u+r`, `ugo-wx`) et octal (`444`, `740`).
- Catégories d’utilisateurs : propriétaire (`u`), groupe (`g`), autres (`o`), toutes (`a`).
- Utilisateur root (superutilisateur) — **à éviter en login direct**.
- Commande `sudo` et fichier `/etc/sudoers`.

### 🔧 Compétences requises
- Navigation dans l’arborescence (`cd`, `ls`).
- Création/répertoire (`mkdir`).
- Compilation/exécution C (`gcc`, `./a.out`).
- Manipulation des permissions (`chmod`).
- Utilisation de `sudo`.

### 📚 Fonctions utilisées & exemples
- `gcc` : compiler un programme  
  → `gcc test.c -o test`
- `chmod` : modifier permissions  
  → `chmod 755 script.sh`

---

## 2. Hiérarchie du Système de Fichiers & Fichiers Spéciaux

### Notions abordées
- Structure en arborescence depuis `/`. "Tout est fichier" (périphériques, noyau...).
- Fichiers spéciaux dans `/dev` : bloc `b` et caractère `c`. Exemples : `/dev/null`, `/dev/urandom`, etc.
- Redirections (`>`, `>>`, `2>`, `/dev/null`).
- Descripteurs : stdin(0), stdout(1), stderr(2).
- Accès noyau via `/proc` et `/sys`.
- Standard FHS : `/bin`, `/etc`, `/home`, `/lib`, `/usr`, `/var`.
- Infos processus : PID, UID, PPID dans `/proc`.

### Compétences requises
- Navigation système, lecture fichiers spéciaux.
- Redirections E/S vers `/dev/null`.
- Identifier PID/UID/PPID.
- Consoles virtuelles : `Ctrl+Alt+F1`...`F6`.

### 📚 Fonctions utilisées & exemples
- `od` : affichage octal/hex  
  → `od -c /dev/urandom | head`
- `echo "abc" > /dev/null` : redirection.
- `cat /proc/1/status` : infos sur le PID 1.
- `id` : afficher UID/GID  
- `ls /sys/class` : voir périphériques.

---

## 3. Liens (Logiques et Physiques)

### Notions abordées
- Numéro d’inode comme identifiant unique.
- Liens physiques (hard links) : mêmes inodes.
- Liens symboliques (soft links) : vers un nom.
- `ls -l` : compteur de liens, type (`-` pour physique, `l` pour symbolique).
- Comportement lors de suppression.
- Liens spéciaux : `.` et `..` sont physiques.

### Compétences requises
- Lire inode avec `ls -li`.
- Créer des liens symboliques et physiques.
- Observer comportements via `ls` et suppression.
- Utilisation de `cp -a` (préserve liens).

### 📚 Fonctions utilisées & exemples
- `stat fichier` : infos détaillées  
- `ls -li fichier` : voir inodes 
- `ln fichier1 fichier2` : creer lien physique.
- `ln -s fichier lien_symbolique` : creer lien symbolique.
- `rm fichier` : suppression du fichier source.

---

## 4. Système de Fichiers Ext2 & Inodes
### Notions abordées
- Ext2 : système à inodes.
- Blocs de taille fixe (1K, 2K...).
- Inodes : type, taille, permissions, pointeurs.
- 15 pointeurs (12 directs + 3 niveaux d’indirection).
- Structure physique : superbloc, groupes, bitmaps, inodes, data blocks.
- Calcul taille fichier max.
- Différence espace disque vs inodes : `df -h` / `df -ih`.

### Compétences requises
- Explorer un système Ext2 monté.
- Lire structure d’un inode.
- Identifier superbloc, bitmaps, table d’inodes.
- Calculer taille maximale d’un fichier en fonction du FS.

### Fonctions & outils typiques
- df(1) : Rapporter l'utilisation de l'espace disque du système de fichiers
- dumpe2fs(8) : Afficher les informations du super-bloc et des groupes de blocs d'un système de fichiers ext2/3/4
- dd(1) : Convertir et copier un fichier (souvent utilisé pour créer des images disque) (pas de section man standard).
- mkfs.ext2(8) : Construire un système de fichiers ext2
- hexdump(1) : Afficher un fichier en hexadécimal et autres formats
- grep(1) : Filtrer des lignes correspondant à un motif
- mount(8) : Monter un système de fichiers sur un point de montage
- sudo(8) : Exécuter une commande en tant que superutilisateur
- umount(8) : Démontrer un système de fichiers

## 5. Examen du Système de Fichiers (debugfs)
### Notions abordées :
- debugfs comme outil interactif pour examiner et déboguer les systèmes de fichiers ext2/3/4 (CM3).
- Accès aux statistiques globales du système de fichiers (super-bloc) via debugfs
- Inspection des informations d'un inode spécifique (statistiques, pointeurs vers les blocs) via debugfs
- Analyser les pointeurs de l'inode pour déterminer les niveaux d'indirection
- Extraire les permissions et l'identifiant d'inode d'un fichier via debugfs

### Fonctions utilisées :
- debugfs(8) : Débogueur de système de fichiers pour ext2/3/4
- echo(1) : Afficher une ligne de texte (utilisé ici pour passer des commandes à debugfs)
- show_super_stats (commande interne debugfs) : Afficher les statistiques du super-bloc
- stat (commande interne debugfs) : Afficher les informations d'un inode

---
📌 **Remarques générales** :
- Toujours tester avec précaution dans `/dev`, `/proc`, `/sys`.
- Bien comprendre la différence entre *lien symbolique* et *copie*.
- Vérifier vos permissions avant d’exécuter des commandes sensibles.
