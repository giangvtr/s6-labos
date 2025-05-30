# LAB 3 : Makefile to install libraries and processes

## 1. Construction et Utilisation de Bibliothèques
### Notions Abordées :

- **L'outil make** : Gestion du processus de construction (build process) pour des projets complexes, incluant des bibliothèques et des exécutables, en utilisant des règles et des dépendances.  
  *(Lien CM5 - Génération de programme, CM2 - Redirection d'exit code && pour enchaîner make et make install)*
- **Les bibliothèques (Libraries)** : Collections de code (fonctions) pour la réutilisation.  
  *(Lien CM5 - Langage C comme langage système, CM3 - Emplacement des bibliothèques /lib, /usr/lib, etc.)*
- **Les bibliothèques statiques (.a)** : Code de la bibliothèque inclus directement dans l'exécutable à la compilation (liaison statique).
- **Les bibliothèques dynamiques / partagées (.so)** : Code de la bibliothèque lié et chargé seulement à l'exécution (liaison dynamique/partagée).
- **Liaison avec des bibliothèques tierces** : Utilisation des options de gcc (`-l`, `-L`).
- **Installation de bibliothèques** : Respect de la hiérarchie du système de fichiers (ex: `/usr/local/lib`) et mise à jour du cache système avec `ldconfig`.  
  *(Lien CM3 - Arborescence standard, CM3 - Configuration de ldconfig)*
- **Permissions et privilèges** : Utilisation de `sudo` pour les opérations système (install).  
  *(Lien CM3 - Droits d'accès, CM3 - Aparté sudoers, Lab 2 - Root user et sudo)*
- **Variables d'environnement** : `$LD_LIBRARY_PATH` (mentionné comme mauvaise pratique pour le système entier).  
  *(Lien CM2 - Variables d'environnement, CM4 - Processus héritent de l'environnement parent, CM5 - Le C et les variables d'environnement)* 
- Utiliser les options du compilateur (gcc) et des outils d'archivage (ar).  
## • Fonctions/Commandes Utilisées :
- `make(1)` : Gérer le processus de construction.  
- `gcc(1)` : Compiler des programmes C, créer des bibliothèques dynamiques (`-shared`, `-fpic`), lier avec des bibliothèques (`-l`, `-L`).  
- `ar(1)` : Créer et manipuler des archives (bibliothèques statiques).  
- `ldconfig(8)` : Mettre à jour les liens et le cache des bibliothèques partagées.  
- `export(1)` : Modifier les variables d'environnement dans le shell courant.  
- `ldd(1)` : Afficher les dépendances des bibliothèques partagées d'un exécutable.  
- `objdump(1)` : Examiner les informations d'un fichier objet (symboles, etc.).

---

## Partie 2 : Introduction aux Processus
### • Notions Abordées :
- **Les Processus (Processes)** : Une instance d'un programme en cours d'exécution, avec son propre espace mémoire et son contexte.  
  *(Lien CM4 - Introduction aux processus)*
- **Identité d'un processus** : Chaque processus a un identifiant unique (PID) et un identifiant de processus parent (PPID).
- **Environnement d'un processus** : Ensemble de variables héritées du parent (`environ`), accessibles et modifiables en C (`getenv`) et en shell (`export`).  
  *(Lien CM2 - Variables d'environnement, CM5 - Accès aux variables d'environnement en C)*

- **Fichiers de configuration Shell (.bashrc)** : Modifier l'environnement de manière permanente pour les sessions de login.  
  *(Lien CM2 - Fichiers de configuration de session)*

- **Création de processus** :  
    * L'appel système `fork(2)` duplique le processus appelant pour créer un enfant.  
    * L'appel système `exec(3)` (et ses variantes) remplace le code binaire du processus appelant par un nouveau programme.  
- **Attente de terminaison** :  
    * L'appel système `wait(2)` permet au parent d'attendre la fin d'un processus enfant.  
- **La pseudo-arborescence `/proc`** : Un système de fichiers virtuel contenant des informations sur les processus et le système.

## • Fonctions/Commandes Utilisées :

- `getpid(2)` : Obtenir l'identifiant du processus courant.  
- `getppid(2)` : Obtenir l'identifiant du processus parent.  
- `getenv(3)` : Récupérer la valeur d'une variable d'environnement en C.  
- `fork(2)` : Créer un nouveau processus par duplication.  
- `exec(3)` (variantes : `execl`, `execv`) : Remplacer le programme en cours d'exécution par un autre.  
- `wait(2)` : Attendre la fin d'un processus enfant.  
- `ps(1)` : Afficher les processus en cours.  
- `top(1)` : Afficher dynamiquement les processus en cours et leurs statistiques.  
- `grep(1)` : Filtrer des lignes de texte (utile pour rechercher un processus dans la sortie de ps ou top).  
- `id(1)` : Afficher l'identité de l'utilisateur (UID, GID).  
- `which(1)` : Afficher le chemin complet d'une commande exécutable.  
- `cat(1)` : Afficher le contenu d'un fichier (utile pour lire les fichiers dans `/proc`).  
- `printf(3)` : Afficher des informations sur la sortie standard.  
- `fprintf(3)` : Afficher des informations sur la sortie standard d'erreur.  
- `perror(3)` : Afficher un message d'erreur système basé sur `errno`.  
- `exit(3)` : Terminer le processus courant avec un code de sortie.

---

## Partie 3 : Contrôle des Processus et Exercices
### • Notions Abordées :
- **Gestion des tâches en cours** : Interrompre (`Ctrl-C`), suspendre (`Ctrl-Z`), relancer en arrière-plan (`bg`) ou avant-plan (`fg`) une commande.  
  *(Lien CM2 - Background, foreground, CM2 - Ctrl+c, Ctrl+z)*

- **Terminaison de processus** : Utiliser la commande `kill` pour envoyer des signaux aux processus, notamment pour les arrêter.  
  *(Lien CM4 - Tuer un processus)*

- **Mise en pratique des processus** : Combiner `fork`, `exec` et `wait` pour créer des hiérarchies de processus exécutant différents programmes.

- **Bonnes pratiques d'installation** :  
  Installer des exécutables dans des répertoires système (`/usr/local/bin`) pour qu'ils soient trouvés via le `$PATH`, en utilisant les règles `install` et `distclean` dans le `Makefile`.  
  *(Lien CM2 - Variable d'environnement PATH, CM3 - Exécutables dans /bin, /usr/bin etc. via $PATH, CM2 - Redirection d'exit code && et make install)*

### • Fonctions/Commandes Utilisées :

- `kill(1)` : Envoyer un signal à un processus.  
- `bg(1)` : Reprendre une tâche suspendue en arrière-plan.  
- `fg(1)` : Reprendre une tâche suspendue en avant-plan.  
- `fork(2)` : Créer un processus enfant.  
- `exec(3)` : Exécuter un programme dans un processus.
