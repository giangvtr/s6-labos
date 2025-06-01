# Correction TP1 : LINUX ET SCRIPTS
## 1) Mini-exos
### Exo 1 : Afficher "Hello !" :

``` bash
#!/bin/bash
echo "Hello !"
```
### Exo 2: Script qui execute ls -aCF
```bash
#!/bin/bash
ls -aCF $
```

### Exo 3: 
Invite l'utilisateur à donner son nom sur le standard input et initialise une variable shell : NAME. Ensuite affiche le contenu
de cette variable

```bash
#!/bin/bash
echo "Please give your name"
read NAME
echo "Your name is $NAME"
```

### Exo 4:
Affiche les variables d'environnements de l'utilisateur et du shell utilisé (printenv pour avoir la liste des variables
d'environnement)

```bash
#!/bin/bash
echo "$USER is using $SHELL"
```

```bash
#!/bin/bash
USER=$(whoami)
DIR=$(pwd)
echo $USER "is using" $DIR
```



### Exo 5: 
Affiche les paramètres (arguments) du programme et le nom du programme. !! Bien mettre (( )) pour l'incrémentation de i
(opération arithmétique) !!
```bash
#!/bin/bash
echo "The script is : $0"
i=
for val in $@; do
  ((i++))
  echo "The parameter $i is $val"
done
```

or
```bash
#!/bin/bash
i=1
script=$(basename $BASH_SOURCE)
echo "The script is : " $script 
for arg do
  echo "The parameter "$i" is : "$arg
  i=$((i + 1))
done
```

### Exo 6: 
Affiche le texte entré malgrès les retour à la ligne (arrête dès qu'une ligne vide)

```bash
#!/bin/bash
SAVE=""
echo "Give your text"

while read LINE; do
  if [ "$LINE" == "" ];
  then break
  else
  SAVE += $LINE
  fi
done

echo -e "Your text is : \n"
echo $SAVE
```
or

```bash
#!/bin/bash
echo "Give your text (When finish type Ctrl+D) !"

#arr is now the array that holds our arguments
readarray -t arr 


echo -e  "Your text is :\n"
echo "${arr[*]}"
```

## Exo 7 : Script to move empty files
```bash
#!/bin/bash
DIR=./empty-files
mkdir "$DIR" -p

nbok=0;
readarray -t fp_array < <(ls -l|awk '$5==0 {print $9}')
echo "This program will move empty files in to $DIR"
for f in "${fp_array[@]}"
do
	mv "$f" "$DIR"
	mvreturn=$?
	if [ $mvreturn -eq 0 ]
	then
	((nbok++))
	fi
done
echo "$nbok files processed correctly"
```

## 2) Sauvegarde image et traitement erreurs
* Demande quelle extension d'image le programme doit sauvegarder
* Vérifie qu'il y a bien un argument (et pas plus) d'indique, sinon affiche un message d'erreur dans le standard error output
* Vérifie qu'il y a bien un fichier avec l'extension à traiter, sinon message d'erreur standard error output 
* Attention : bien sortir dans le cas d'une erreur : exit 1
indiquer que le message d'erreur va dans le standard error output : echo "erreur ..." >&

``` bash
#!/bin/bash
if [ $# -ne 1 ]
    # '$#': special variable that holds the number of arguments passed to the script.
    # -ne 1: Checks if the number of arguments is not equal to 1. 
    then
    echo "This program should have one argument" >&
    exit 1
fi

DIR=original_images;

# Creates the directory original_images if it doesn’t exist (-p prevents errors if it already exists)
mkdir $DIR -p

i=1
nbok=0
EXTENSION=$1

# Finds & count lines that start with - (regular files) and end with the given extension.
nb=$(ls -l | grep "^-.*\.$EXTENSION$" | wc -l)

# Checks if nb is 0 (no files found)
if [ $nb -eq 0 ]
    then
    echo "$0 has no file to process" >&2
    exit 1
    # Exits with an error
fi
echo "This program will backup and rename $nb $EXTENSION files"

for f in *.$EXTENSION
    do
    cp $f $DIR
    mv $f $(printf "image_%0.3d.$EXTENSION" $i)
    # %0.3d means 3 digits with leading zeros
    mvreturn=$?        # $? is the exit status of the last command (mv). 0 means success.
    if [ $mvreturn == 0 ]
        then
        ((nbok++))
    fi
    ((i++))
done

echo "$nbok files processed correctly"
```

or 
```bash
#!/bin/bash	
DIR=original_images;
mkdir "$DIR" -p;	
i=1
nbok=0

#ensure that the command has 1 argument
if [[ -z "$1" ]]; then
    echo "This program should have one argument (file extension)." >&2
    exit 1
fi

#to take command line argument
arg="$1"

#count nb of .$arg files
nb=$(ls -l | grep "^-.*\.${arg}$" | wc -l)

if [ $nb -eq 0 ]; then
	echo "$0 has no file to process" >&2
	exit 1
fi

echo "This program will backup and rename $nb .$arg files"
for f in *.$arg
do
      cp "$f" "$DIR"
      mv "$f" "$(printf "image_%0.3d.${arg}" $i)"   
      mvreturn=$?
      if [ $mvreturn -eq 0 ]
      then
      	((nbok++))
      fi
      ((i++))
done
echo "$nbok files processed correctly"

```

## 3) Traitement IP Adresse
Télécharger un des fichier : `wget -O`, ensuite indique que tous les fichiers sont concatenés en un seul et -O- indique que ce
fichier doit être écrit dans la standard output

```commandline
wget -O - "https://www.cjoint.com/doc/23_03/MCBn305uIy7_sysmic-org-access.log.gz"
```

Décompresser un fichier

```commandline
zcat MCBn305uIy7_sysmic-org-access.log.gz
```

Trier les adresses IP du ficher à partir en fonction du nombre d'accès (ordre décroissant) et les enregistre dans un
nouveau fichier

```commandline
grep -E "^([0-9]+\.){3}[0-9]+" MCBn305uIy7_sysmic-org-access.log -o | sort | uniq -c | sort -n > resultat.txt
```
* Utiliser _uniq -c_ pour avoir le nombre de doublons. 
* Faire un _sort_ avant _uniq_ pour qu'il détecte tous les doublons (et pas que ceux qui se suivent).

2ème sort :

> -n : indique qu'on trie des nombres, évite les problèmes avec des espaces (11 < ·8 par exemple).
>
> -r : indique l'ordre décroissant.

* Enregistrer les résultats dans le fichier : > resultat.txt

```bash
#!/bin/bash
URL=https://www.cjoint.com/doc/23_03/MCBn305uIy7_sysmic-org-access.log.gz
nomFich=MCBn305uIy7_sysmic-org-access.log
wget $URL
zcat $nomFich.gz
grep -Eo "^([0-9]+\.){3}[0-9]+" $nomFich | sort | uniq -c | sort -nr > resultat.txt
```
or
```bash
#!/bin/bash

# URL of the file
URL="https://www.cjoint.com/doc/23_03/MCBn305uIy7_sysmic-org-access.log.gz"

# Download, decompress, filter, extract IPs, count occurrences, and save to file
wget -O - "$URL" | zcat | egrep -o '^\d+\.\d+\.\d+\.\d+\b|^([a-fA-F0-9]+\:){7}[a-fA-F0-9]+\b' | sort | uniq -c > frequency.log

# Sort numerically and output the most frequent IPs
sort -nr frequency.log | awk '{print $2}' > result.log

```

Même chose mais en pipelining et pas un script : Juste une seule ligne avec plusieurs commandes séparées par |
```commandline
wget https://www.cjoint.com/doc/23_03/MCBn305uIy7_sysmic-org-access.log.gz | zcat MCBn305uIy7_sysmic-org-access.log.gz | grep -Eo "^([0-9]+\.){3}[0-9]+" $nomFich | sort | uniq -c | sort -nr > resultat.txt
```


