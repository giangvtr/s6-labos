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
- `df -h` : espace disque utilisé  
  → `df -h /mnt/ext2disk`
- `df -ih` : utilisation des inodes  
  → `df -ih /mnt/ext2disk`
- `dumpe2fs` : analyser structure Ext2  
  → `sudo dumpe2fs /dev/sdX1`
- `debugfs` : inspecter inode, blocs  
  → `sudo debugfs /dev/sdX1`

---

📌 **Remarques générales** :
- Toujours tester avec précaution dans `/dev`, `/proc`, `/sys`.
- Bien comprendre la différence entre *lien symbolique* et *copie*.
- Vérifier vos permissions avant d’exécuter des commandes sensibles.
