# Recherche de texte et d'entrées, expressions régulières

*Programmation système d'exploitation - Muriel Pressigout - V2024-04-05*

Ceci est un notebook, les cellules sont éditables. 
Une cellule commençant par \$ est un texte qui correspond à une commande à tester dans le terminal. Vous pouvez copier-coller facilement les commandes demandées dans un terminal et y écrire vos résultats. C'est un sujet-feuille de réponse. 

Pour exporter ce document en pdf : File -> Export Notebook as... -> PDF. 

NB : vous pouver ouvrir ce fichier dans un navigateur sous Google colab, ce qui permet de lire et écrire dans ce fichier sans installation au préalable. Cependant vous n'aurez pas l'export en pdf.

Commencez par ouvrir un terminal dans le même répertoire que ce notebook.
Testez :

``` $ ls ```

Vérifiez que vous avez bien les fichiers suivants dans le répertoire courant:
* passwd
* some-text.txt
* tuto-expressions-regulieres.ipynb
* auth.log

## Contexte 

* Activité d'administration système (multi-utilisateur, réseau, distant, embarqué,...):
    * manipulation de fichier de configuration
        * lecture
        * écriture
    * exploitation de fichiers de log
    *...
    
Face à un fichier en format texte, savoir rechercher une valeur ou un **motif** avec les outils/langages/concepts adéquats permet d'effectuer ces tâches avec une efficacité ++

* Par généralisation, toute lecture/exploitation d'un fichier de données sera extrêmement rapide en exploitant la structure connue des données 
    * Recherche de motif existe sous python : module re 
    


**Les expressions régulières sont par conséquent utiles, concises et génériques pour extraire des informations de textes comme du code, des données, des fichiers de log, des feuilles de calcul ou des documents.**

### Exemples 


* Recherche du motif "you" dans "some-text.txt" :

``` $ grep "you" some-text.txt ```

On obtient toutes les **lignes** où se trouve la chaîne de caractères "you", y compris donc celle avec le mot "your". Les **valeurs** (**occurences**) trouvées sont en gras et en couleur.

Autre exemple sur un fichier de log, /var/log/auth.log. Il contient un historique des actions d'authentification sur Linux. Vous pouvez jeter un coup d'oeil au contenu :

``` $ sudo cat /var/log/auth.log ```

Comme il est protégé, une copie d'un tel fichier est fourni. Vous pouvez vérifier son contenu :

``` $ cat auth.log ```

Si on veut voir toutes les informations liées au compte eii, on peut utiliser grep:

``` $ grep "eii" auth.log ```

Si on veut affiner notre recherche pour n'avoir que les ouvertures de session de eii:

``` $ grep "session opened for user eii" /var/log/auth.log ```

Et enfin, on veut finalement avoir les jours où une session où eii a ouvert une session, sans doublon:

``` $ grep "session opened for user eii" auth.log | grep -oE "^[^[:space:]]+[[:space:]]+[0-9]{1,2}" |sort |uniq ```

Les expression régulières peuvent être un des outils pour détecter des anomalies sur un système. Par exemple, vous pouvez analyser régulièrement le fichier auth.log pour voir si quelqu'un est en train d'essayer de se logger en admin et de craquer le mot de passe. Dans ce cas, on va chercher le message type d'erreur, par exemple "incorrect password" ou "authentication failure":

``` $ grep -E "(incorrect password)|(authentication failure)" auth.log ```

L'idée est ensuite de faire remonter le résultat de cette analyse à intervalle régulier à une application qui monitore la sécurité d'un serveur par exemple. Vous pouvez regarder après la séance un type de réalisation ici : [https://betterstack.com/community/guides/logging/monitoring-linux-auth-logs/](#https://betterstack.com/community/guides/logging/monitoring-linux-auth-logs/)

Le but de cette séance est qu'à a la fin vous comprenez cette dernière ligne et que vous soyez capable d'écrire ce genre de recherche.
Pour cela, on va d'abord voir ce qu'est une expression régulière, sa syntaxe et son usage avec la commande grep. Puis ensuite on verra comment combiner une commande grep avec d'autres commandes. Il y a 3 exercices au fur et à mesure de la progression pour valider les acquis.


**EVAL** : cette partie sera évaluée au DS TP en testant  votre capacité à former une expression régulière pour filtrer un texte en utilisant la commande grep et les autres commandes utiles vu dans ce CM-TD.

<div id='regex'/>

## Regex

regex = diminutif d'**expressions regulières**


### Definitions

**Expression régulière** = **motif**(pattern) correspondant (matching) à un **ensemble** de chaînes de caractères recherchées.

Pour avoir uniquement le mot "you", le motif à appliquer préciserait qu'il ne faut aucune lettre devant ni derrière la chaîne de caractère "you" (on ne vous demande pas de comprendre l'expression régulière pour l'instant). Vous pouvez vérifier la différence :

``` $ grep "you" some-text.txt ```

``` $ grep "\byou\b" some-text.txt ```

Le motif représentant l'expression régulière "you" est "you" et celui représentant le mot "you" est "\byou\b". Il faut donc lire attentivement les consignes &#x1F600; Et comme souvent, il y a plusieurs solutions, l'essentiel c'est que vous trouviez votre façon de faire en vous inspirant des bonnes pratiques. 
De manière générale, il faut réflechir à ce que l'on veut trouver mais aussi à ce que l'on ne veut pas trouver.

Les **métacaractères** sont des caractères qui jouent un rôle autre que leur signification ASCII. Dans l'exemple du haut, le caractère 'b' est utilisé dans l'expression régulière mais pour autre chose que le caractère ASCII 'b'. On verra plus tard  les détails mais grâce à eux, "\b" veut dire "détecter la limite d'un début de mot". La représentation exhaustive de toutes les combinaisons à éviter (chiffre, ponctuation, espaces,...) serait plus long, voire difficile dans certains cas.
**On utilisera l'option -E de grep pour que tous les métacaractères jouent leur rôle de métacaractères par défaut.**

### Commande-grep 

Dans les exemples utilisés précédement, la commande lancée est `grep`. C'est la commande sous Linux qui prend en argument un motif et va le chercher soit sur la sortie standard ou le cas échéant dans le nom de fichier donné en paramètre:

``` $ man grep```

Il y a des options à cette commande qui sont rapidement utiles:

* -c : donne le nombre de lignes avec au moins une occurence trouvée
* -r : recherche récursive sur le répertoire courant
* -o : n'affiche que les occurences trouvées
* -i : ignore la casse
* -n : ajoute le numéro de la ligne où l'occurence est trouvée
* -E : permet d'utiliser les métacaractères facilement (quasi obligatoire dès qu'on les utilise)

Testez :

``` $ grep "sudo" auth.log```

``` $ grep "sudo" auth.log -n```

``` $ grep "sudo" auth.log -c```

``` $ grep "sudo" -r -n```

``` $ grep "sudo" -r -n -c ```

``` $ grep "pwd" auth.log ```

``` $ grep "pwd" auth.log -i```

**Conseil** : vérifier la sortie de votre commande grep avant d'y ajouter une option, surtout l'option -c 

### Construction


Une expression réulière se construit à partir de briques de base que sont les ERA (Expression Régulière Atomique) qui peuvent être combinées : 
* concaténation
* répétition
* alternative
* références arrière

On peut aussi spécifier leur place dans la ligne de texte grâce aux ancres de début et fin de ligne.

Tout ceci est décrit par la suite, avec des exercices pour pratiquer.

#### ERA

La brique de base est une **ERA** (Expression Régulière Atomique) = un caractères parmi ces possibilités :

1. un caractère de base:

|ERA|Exemple|Caractère possible|
|:--|:--|:--|
|Un caractère ASCII | A | La lettre A|
| . | . | N'importe quel caractère|
|Un caractère parmi un ensemble | [abc] | le caractère a **OU** b **OU** c|
|Exclusion d'un ensemble | [^abc] | Tout caractère sauf a ou b ou c|
|Tout caractère dans un intervalle | [a-z] | Une lettre alphabétique minuscule|
|Exclusion d'un intervalle | [^a-z] | Tout sauf une lettre alpha. minuscule|

2. un caractère appartenant à une de ces classes de caractères:

|Classe|Caractère possible|
|:--|:--|
|[:lower:] | une lettre minuscule|
|[:upper:] | une lettre majuscule |
|[:alpha:] | un alphabétique: [:lower:] and [:upper:]|
|[:digit:] | un digit = [0-9]|
|[:alnum:] | un alphanumérique: [:alpha:] and [:digit:]|
|[:punct:] | un caractère de ponctuation| 
|[:graph:] | un caractère graphique: [:alnum:] and [:punct:] |
|[:blank:] | espace ou tab|
|[:space:] | [:blank:] + special caracters used in C for space characters : \t,\n,\r|
|[:print:] | un caractère imprimable :[:graph:] and [:space:] |
|[:cntrl:] | un caractère de contrôle (début de la table ASCII, char<32)| 
|[:xdigit:] | un digit en hexadecimal = [0-9A-Fa-f]|

Attention, suivant l'encodage, [:lower:] n'est pas équivalent à [a-z], par exemple pour la prise en compte des accents.

Les métacaractères perdent leur caractère spécial à l'intérieur des crochets []:
* Pour inclure le caractère ] dans un ensemble, le mettre au début, par ex : []a-z] veur dire tout caractère de a à z ainsi que ]
* Pour inclure le caractère - dans un ensemble, le mettre à la fin, par ex : [a-z-] veur dire tout caractère de a à z ainsi que -
* Pour inclure le caractère ^ dans un ensemble, le mettre partotu sauf au début, par ex : [^a-z^] veur dire tout caractère sauf (les caractères de a à z et ^)

3. PCRE
Certaines classes de caractères permettent d'écrire plus facilement certaines expressions. Ce sont les PCRE (Perl Compatible regular Expression), que l'on retrouve dans pleins de langages scripts, dont Python:

|Classe|Caractère possible|
|:--|:--|
|\< | correspond à la chaîne vide au début d'un mot|
|\> | correspond à la chaîne vide à la fin d'un mot|
|\b | correspond à une chaîne vide près d'un mot (limite d'un mot)|
|\B| correspond à uen chaîne pas à c$oté d'un mot (limite de quelquechose qui n'est pas un mot) |
|\w | un caractère dans un mot. Equivalent à [_[:alnum:]]| 
|\W | un caractère qui n'est pas dans un mot.  Equivalent à [^_[:alnum:]]|
|\s | un blanc. Equivalentà [:space:]| 
|\S | tout sauf un blanc.  Equivalent à [^[:space:]]|

Comme leur présence se retrouve dans d'autres outils de script, essayez de privilégier leur utilisation quand vous avez le choix entre plusieurs écritures.

4. autres caractères spéciaux :

|Caractère spécial|Signification|
|:--|:--|
|\0 | le caractère \<null\>
|\\a | le caractère \<bell\>
|\\b | le caractère \<backspace\>
|\\f | le caractère \<form-feed\> 
|\\n | le caractère \<new-line\>
|\\r | le caractère \<carriage-return\>
|\\t | le caractère \<tab\>
|\\v | le caractère \<vertical-tab\>
|\\013 | le caractère dont le code ASCII est 013 en octal


Comme en C, le caractère \\ sert à changer le rôle d'un caractère (on dit échapper un caractère). Par exemple \\. permet d'obtenir le caractère ASCII '.' alors que par défaut il s'agit du métacaractère qui remplace n'importe quel caractère.

Testez :

```$ grep -E "." some-text.txt ```

``` $ grep -E "\." some-text.txt ```

#### Concatenation 

**Concaténation** d'expressions: mettre les expressions les unes à la suite des autres

##### Exemples :


|Expression régulière|Signification|Chaînes de caractères correspondantes|
|:--|:--|:--|
|abc | la chaîne de 3 caractères "abc"| 1 seule possibilité : "abc" |
|[Oo]ui | le mot  "oui", initiale en maj ou non| 2 possibilités : "oui", "Oui"|
|[a-z][0-9] | une minuscule puis un digit|260 combinaisons : a0,...a9,b0,...,z9|
|[a-z][0-9]. | une minuscule, un digit puis un quelconque | a0a, a02, a0!, ...|

#### Repetition



On peut faire une **répétition** d'un item:

|Motif | Correspondance|
|:--|:--|
| ? | L’item précédent est optionnel et si présent : **au plus une fois**|
| * |L’item précédent est présent **zéro fois ou plusieurs fois**|
| + | L’item précédent est présent **au moins une fois ou plus**|
| {n} |L’item précédent est présent **n fois exactement**|
| {n,} |L’item précédent est présent **n fois ou plus**|
| {,m} | L’item précédent est présent **m fois au plus**|
| {n,m} | L’item précédent est présent **entre n et m fois**|

On peut parenthèser l'item que l'on veut répéter.

Exemples:

|Motif |Correspondance(s)|
|:--|:--|
| abc | la chaîne abc |
| a\\. | la chaîne de 2 caractères a. |
| a. | une chaîne de 2 caractères commençant par a |
| a? | chaîne vide ou la chaîne a |
| a+ | la chaîne aa ou  aaa ou  aaaa ou aaaaaaaaaaaaaaaaaaaaaaaaaaa ....|
| a* | chaîne vide ou aa ou aaa ou aaaa ou aaaaaaaaaaaaaaaaaaaaaaaaaaa .... |
| a{2} | la chaîne aa |
| a{2,5} | la chaîne aa ou la chaîne aaa ou la chaîne aaaa ou la chaîne aaaaa|
| [ab]{2} | la chaîne aa ou la chaîne ab ou la chaîne ba ou la chaîne bb |
| ab{2} | la chaîne abb |
| (ab){2} | la chaîne abab |



Autre exemple : voici la commande pour chercher dans le fichier some-text.txt toutes les lignes où il y a **un mot suivi d'une ponctuation**. Attention, il peut y avoir un ou plusieurs espaces entre le mots et le caractère de ponctuation.

``` $ grep -E "[[:alpha:]]+[[:space:]]*[[:punct:]]" some-text.txt ```

Pour n'avoir que les mots suivis d'un symbole de ponctuation, avec éventuellement un ou plusieurs espaces entre, il faut enchainer 2 grep avec l'option -o: le premier pour avoir les mots avec la ponctuation puis juste le mot. Cela donne :


``` $ grep -E "[[:alpha:]]+[[:space:]]*[[:punct:]]" some-text.txt -o | grep -E "[[:alpha:]]+" -o ```

Il y a une redirection d'E/S : le 2eme grep prend en entrée le résultat du premier grep. Une bonne habitude est de décomposer le problème : regarder ce que fait le 1er grep puis lui rajouter un traitement derrière si nécessaire.

#### Alternative

Syntaxe de l'**alternative** entre 2 expressions: ceci | cela


Exemples:
 * (linux)|(unix): le mot linux ou le mot unix
 * [A-Z]{8}|[0-9]{4} : 8 lettres majuscules ou 4 chiffres

#### Exercice-1

Avant de continuer sur les possibilités des expression régulières, voici un exercice sur le fichier "some-text.txt".

Ecrire la commande grep qui donne :
* Toutes les lignes avec un mot d'au moins 7 lettres (vous devriez trouver 24 lignes)

Réponse : ```grep -E "\b[a-zA-Z]{7,}\b" some-text.txt ``` (-c to count number of lines)

* Tous les mots d'au moins 7 lettres (vous devriez en trouver 37)

Réponse : ```grep -E "\b[a-zA-Z]{7,}\b" some-text.txt -o``` (-o|wc for counting words)

Conclusion : grep -c counts the number of lines with a matched texts but it does not count not the number of matched texts. For this, you should use grep -o |wc

* Toutes les lignes avec les mots then ou thee  (vous devriez en trouver 3)

Réponse : ```grep -E "\b(then)|(thee)\b" some-text.txt```

#### Ancrage 

Il peut être utile voire indispensable de situer l’expression régulière cherchée par rapport au début et/ou la fin de ligne. On utilise pour cela deux métacaractères: ^ et \$ :
*  ^ désigne le **début** de ligne **s’il est placé au début de l’expression**, sinon c'est le caractère ^
*  \$ désigne la **fin** de ligne **s’il est placé à la fin de l’expression**, sinon c'est le caractère \$

Situer un motif par rapport à un repère de la ligne = **ancrage** (*anchoring*).

Exemple:

|Motif|Correspondance|
|:--|:--|
| ^linux | toute ligne commençant strictement par le mot linux|
| linux\$ | toute ligne finissant strictement par le mot linux|
| ^linux\$ | les lignes ne comportant strictement que le mot linux|
| \$linux | toute ligne avec le texte \$linux quelque part|


#### Reference-arriere

Nous avons déjà vu que [of]{2} correspond à  oo ou of ou fo ou ff et non seulement oo ou ff. En effet, les répétitions vues jusque là sont des répétitions du motif et non d'une valeur trouvée. Pour retrouver une valeur, on en fera une sous-expression et on utilisera une référence arrière pour y faire référence. Voici comment faire:
   * les parenthèses () permettent de grouper des ERA pour délimiter une **sous-expression**.
   * la notation **\\n** (n étant un digit) est une **référence arrière** (*back-expression*)  à la **n**ième sous-expression trouvée placée entre ()

Exemple : testez et comprenez bien l'expression régulière recherchée par ces commandes:

```
$ grep -E "[of]{2}" some-text.txt
$ grep -E "([of])\1" some-text.txt
$ grep -E "([[:punct:]]).*([[:punct:]]).*\1.*\2" some-text.txt 
$ grep -E "([A-Z]{2,}).*([eth])+.*\2.*\1" some-text.txt 
```
(1) Highlight all words with oo, of, fo, or ff
(2) Show all lines and highlight words with strictly "oo" or "ff"
(3) A punctuation followed by n'importe quoi caractere plusieurs fois, then another groupe like that. le \2 exige que le premier caractère de ponctuation (groupe 1) réapparaisse plus tard dans la ligne, suivi du second caractère (groupe 2). Between these two punctions, n'import quoi can be injected. A matching group is limited in a ().
(4) Group 1: Any word that has at least 2 capital letter (here is ARTHUR). Group 2: Any word that has letter 'e', 't', 'h' in that (here is helmet). And the group 2 has to be followed by group 1 and between these two groups, other characters are allowed.
#### Metacaracteres

On a vu les différentes syntaxes possibles pour former une expression régulière.

Voici les métacaractères vus ici :      ```| . * + ? ^ \$ ( ) [ ] { } \\ -```

Ils peuvent varier suivant le langage d'expressions régulières.  En ce qui nous concerne, leur comportement est décrit dans la doc de grep. Allez y jeter un coup d'oeil:

```$ man grep ```

et tapez /REGULAR EXPRESSION pour accéder directement à la section qui décrit la syntaxe des regex avec grep.

### Exercices 

#### Exercice-2 

En travaillant avec le fichier "some-text.txt", écrire la commande grep qui donne :
* Toutes les lignes commençant stricyement par une lettre majuscule (pas d'espaces devant) (vous devriez trouver 2 lignes)

Réponse :```grep -E "^\b[A-Z]{1,}.*" some-text.txt```

* Toutes les lignes commençant par une lettre majuscule avec potentiellement des espaces devant et finissant par un point (vous devriez trouver 29 lignes)

Réponse : ```grep -E "^[[:space:]]*[A-Z].*\.$" some-text.txt -c```

* Toutes les lignes contenant deux fois le texte "you" (il n'y en a qu'une)

Réponse : ```grep -E "(you).*\1" some-text.txt```

* Toutes les lignes contenant un mot répété deux fois avec la même casse (vous devriez trouver 7 lignes)

Réponse : `grep -E "(\b\w+\b).*\b\1\b" some-text.txt`

* **(Difficulté ++ : à ne faire que s'il vous reste au moins 1h, skip it otherwise)** Les mots répétés deux fois sur la même ligne (seulement les mots) sans doublons. Il y en a 6  et il faut enchainer 3 grep pour y arriver:  (mode EXPERT)
    * le 1er est celui de la question précédente avec l'option -o pour obtenir les occurences
    * le 2eme pour récuper le premier mot avec l'espace devant éventuellement
    * le 3eme pour récuperer le mot sans l'espace
    * puis sort et uniq pour supprimer les doublons

Réponse : 

#### Exercice-3
On va travailler avec un fichier de config classique sous Linux : /etc/passwd. Il contient les informations sur les utilisateurs. Chaque ligne a 7 champs delimités par le caractère : sous le format suivant

```login:password information:uid:gid:user description:home directory:login shell```

Le champ "user description" peut lui-même contenir des champs (numéro de tel, adresse,...) séparés par le caractère ,

Vous pouvez jeter un coup d'oeil à celui de votre session:

```
$ cat /etc/passwd
```

Au lieu de travailler sur un fichier admin, un fichier de même type vous est fourni dans le répertoire courant : le fichier "passwd".

Vous pouvez vérifier son contenu:

```
$ cat passwd
```

Vous devriez obtenir:

```
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/usr/sbin/nologin
man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
slaurel:x:1001:5000:stan laurel,stan.laurel@film.org, binome de oliver hardy:/home/slaurel:/bin/bash
ohardy:x:1002:5000:oliver hardy,oliver.hardy@film.org, binome de stan laurel:/home/ohardy:/bin/bash
cchaplin:x:1004:5001: charlie chaplin, homeless @Hollywood:/home/guest:/bin/bash
bkeaton:x:1005:5002:do some charlie chaplin bashing:/home/bkeaton:/usr/sbin/nologin 
slaureline:x:1006:0:looking for valerian at 65534 Mulholland Drive:/home/slaureline:/usr/sbin/nologin
nobody:x:65534:65534:nobody,no /home:/nonexistent:/usr/sbin/nologin
```

* toutes les lignes avec une adresse email

Réponse : `grep -E "\b[a-zA-Z0-9._%+-]+\@[a-z]+\.[a-z]+(\.[a-z]+)*\b" passwd`

* toutes les adresses email uniquement

Réponse : `grep -E -o "\b[a-zA-Z0-9._%+-]+\@[a-z]+\.[a-z]+(\.[a-z]+)*\b" passwd`

* toutes les lignes dont le login est strictement slaurel (une seule normalement)

Réponse : `grep -E "\bslaurel\b" passwd`

* toutes les lignes où l'uid contient le digit 0 (6 normalement)

Réponse :`grep -E "^[a-z]*\:[a-z]+\:[0-9]*[0]" passwd`


* toutes les lignes où l'uid vaut 0 (une seule normalement)

Réponse : `grep -E "^[a-z]*\:[a-z]+\:[0]" passwd`

* le login du user dont l'uid vaut 0 (root normalement)

Réponse : `grep -Po "^[^:]+:[^:]+:[0]" passwd | cut -d':' -f1` or `awk -F: '$3 == 0 {print $1}' passwd`

* toutes les lignes où le gid vaut 65534 (2 normalement)

Réponse : `grep -E "^[^:]+:[^:]+:[0-9]+:65534"`

* toutes les lignes où le login shell est bash (4 normalement)

Réponse : `grep -E "\bbash\b$"`

* toutes les lignes où le home directory est /usr/sbin (1 seule normalement)

Réponse : `grep -E \/usr\/sbin:[^:]+$`

* toutes les lignes où le login fait exactement 4 lettres (3 normalement)

Réponse : `grep -E "^[a-z]{4}:" passwd`

* toutes les lignes où le login fait au moins 4 lettres (11 normalement)

Réponse : `grep -E "^[a-z]{4,}:" passwd`

* toutes les lignes où le home directory est dans /home (5 lignes normalement)

Réponse : `grep -E "home\/[a-z]*:[^:]+$" passwd`

## Autres-commandes-utiles  

L'efficacité et l'utilité du grep est la plupart du temps multipliée quand cette comande est utilisée avec d'autres commandes: ls, cut, sort, uniq, find.

Nous allons faire un petit tour de cas d'usage qu'il faut savoir maîtriser.

### ls

On a vu en cours que l'on pouvait chercher avec ls et le globbing des entrées avec un nom générique:

``` $ ls *.pdf     # permet de chercher toutes les entrées finissant par l'extension pdf ```

Première remarque : attention, derrière toute autre commande que grep, les métacaractères sont utilisés pour du globbing (extension de paramètres) et donc les significations des métacaractères est différente. Exemple de différences:

| Caractère | Globbing | Expressions régulières |
|:--|:--|:--|
|. | Caractère ASCII '.'|N'importe quel caractère. | 
| * | Toute chaîne, éventuellement vide | Répétition de 0 ou + ce qui précède|

On peut combiner ls et grep pour faire étendre les possibilités de recherche, notament sur les détails d'une sortie d'un ls -l. Par exemple, ne garder que la liste des entrées qui sont des fichiers :

```
$ ls -l | grep -E "^-"
```

### cut 

Le fichier "passwd" vu précédemment a un format de ligne où chaque champ est séparé par un caractère défini, ici ':'. Ce caractère est appelé le "séparateur".
C'est le cas des fichiers .cvs où les valeurs de chaque colonne sont séparés par des ';' ou des ','.
Chercher un champ dans ce genre de ligne peut se faire avec grep, comme vous avez du le faire dans l'exercice sur le fichier passwd. Par exemple, pour filtrer le champ sur les informations sur le mot de passe, on peut écrire:

``` $ grep -E -o "^[^:]+:[^:]+:" passwd | grep -oE "[^:]+:$" | grep -oE "[^:]+"```

Il faut savoir le faire mais aussi savoir qu'il existe une commande **cut**  qui permet d'extraire automatiquement des parties de ce genre de texte (appelés sections dans la doc de **cut(1)**).

Par exemple, pour aller chercher les gid, on ira cherche le 4eme champ, en indiquant que le caractère séparateur de champ est ':'

```
$ cat passwd | cut -f 4 -d :```

Cela suppose ques informations recherchées sont à une place bien définie. Par exemple, on peut aller chercher la description des utilisateurs

``` $ cat passwd | cut -f 5 -d :```

Puis chercher le 2eme sous-champ de ce champ:

``` $ cat passwd | cut -f 5 -d : | cut -f 2 -d ,```

Cependant, ces sous-champs ne sont pas ordonnés, donc pour chercher une adresse mail, on est obligé de chercher avec grep:

``` $ cat passwd | cut -f 5 -d : | grep -oE "[^@[:space]]+@[^@[:space]]+\.[^@[:space]]+" ```

Notez que cut pourrait être utile pour filtrer une sortie de ls -l en prenant l'espace comme séparateur, par exemple ici pour récuperer les usernames des propriétaires des entrées:

``` $ ls -al | cut -f 3 -d ' ' ```

Cependant, pour respecter l'alignement à l'affichage, il y a parfois plusieurs espaces, ce qui en fait une fausse bonne idée. Cela est encore plus visible sur la racine :

``` $ ls -al / | cut -f 3 -d ' ```

Pour récupérer le nom des propriétaires des entrées, il faudrait combiner un ls -l et un grep

``` $ ls -al | grep -oE "^[^[:space:]]+[[:space:]]+[^[:space:]]+[[:space:]]+[^[:space:]]+" |grep -oE "[^[:space:]]+$" ```

### sort-uniq 

Lorque l'on va chercher les valeurs d'un champ dans un fichier, on veut parfois trier et éliminer les doublons de la sortie. Il y a pour cela respectivement les commandes **sort(1)** et **uniq(1)**.

Par exemple, la liste des propriétaires d'entrées sur le répertoire home de l'utilisateur :

``` $ ls -al ~ | grep -oE "^[^[:space:]]+[[:space:]]+[^[:space:]]+[[:space:]]+[^[:space:]]+" |grep -oE "[^[:space:]]+$" | sort | uniq ```

### find 

On a vu quelques exemples précédement où ls et grep sont combinés pour faire une recherche de fichier. Encor eune fois, c'est bien de savoir le faire mais il faut savoir qu'il existe une commande de recherche d'entrée puissante : **find(1)**. Elle a des très nombreuses options de recherche et permet également d'appliquer un traitement sur les entrées trouvées.

#### Quelques options de recherche de find

La recherche est récursive. Les options de recherche peuvent se cumuler:

* recherche sur le nom
    * globbing possible

``` $  find <repertoireDeDepart> -name "entryname" -print ```

``` $  find /usr/include -name "glob*" -print ```

* recherche par type d'entrée

``` $ find /usr/include –type f -name «*conf*» -print ```

``` $ find /usr/include –type d -name «*conf*» -print ```

* recherche par la taille

``` $ find /usr/bin –size +10M ```

``` $ find /usr/bin –size +10M –size -40M ```

* recherche par la date : -atime, -ctime -mtime

``` $ find /var/log –atime -1``` 

``` $ find /var/log –atime +90``` 

``` $ find /var/log –atime 30``` 

* recherche par l'utilisateur, le groupe

``` $ find /tmp –user eii ```

``` $ find /tmp –uid 1000 ```

``` $ find /tmp –group eii ```

``` $ find /tmp –gid 5000 ```

* test si entrée vide

```
$ find /tmp -empty ```

* recherche en fonction des permissions

``` $ find . –type f –perm 777 –print ```

``` $ find . -type f ! –perm 777 -print ```

#### Appliquer un traitement aux entrées trouvées 

Remplacer -print par -exec commande
   * {} identifie l’entrée trouvée pour la passer en paramètre de la commande
   * fin de la commande par \;

``` $ find / -uid 1000 –exec chown eii {}\;                       #cherche à partir de la racine les entrées dont le propriétaire a l'iud 1000 pour en transférer la propriété à l'utilisateur eii ```

``` $ find /tmp –type f –name « *.test » -exec rm –i {}           # cherche les fichiers finissant par l'extension ".test" pour les supprimer. l'option de rm -i est utile comme protection dans ce cas-là ```

``` $ find . –name « *.c » -exec grep ‘#include’ {} \;            # cherche à partir du répertoire courant toutes les lignes d'include dans les fichiers sources .c```



## Perspectives

Il existe d'autres outils ou langages pour exploiter les expressions régulières:

* sed(1) : stream editor :
    * Cherche un motif et **modifie** le flux associé efficacement
    * Encore plus puissant mais pas intuitif au premier abord

``` $ sed ‘/^#/d’ test.txt             #grep -E "^[^#]" test.txt```

``` $ sed –n ‘/^#/p’ test.txt          #grep -E "^#" test.txt```

``` $ sed ‘s/Hellco/HELLO/’ test.txt    #remplace Hello par HELLO :pas d’équivalence avec grep/egrep qui ne peut pas modifier/traiter le motif trouvé```

``` $ sed –z ‘s/\n/ /g’ test.txt       #pas d’équivalence, même raison```

``` $ for f in *.mp4;do fn=`echo $f|sed ‘s/-/_/g’`; mv « $f » « $fn »; done```



* awk(1) : analyse de motifs et traitement de texte

* python : voir : https://docs.python.org/fr/3/howto/regex.html: vous en ferez en 4EII

* Bonnes pratiques sur les expressions régulières, voir l'introduction de [https://blog.stephane-robert.info/docs/developper/expressions-regulieres/](#https://blog.stephane-robert.info/docs/developper/expressions-regulieres/)


---------------------------
License for the whole document : CC-BY-NC-ND (mpressig@insa-rennes.fr)


```python

```
