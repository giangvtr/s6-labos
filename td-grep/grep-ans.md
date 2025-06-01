## Exercice 2
Q2.1) Toutes les lignes commençant par une lettre majuscule (vous devriez trouver 2 lignes) :

`grep -E “^[A-Z]” some-text.txt`

Q2.2) Toutes les lignes commençant par une lettre majuscule avec potentiellement des espaces devant et finissant par un point :

`grep -E "^ *[A-Z].*\.$" some-text.txt`

Q2.3) Toutes les lignes contenant deux fois le mot “you” :

`grep -E "^.*(you).*\1.*$" some-text.txt`

Q2.4) Toutes les lignes contenant un mot répété deux fois avec la même casse :

`grep -E "[^[:alpha:]]([:alpha:]+)[^[:alpha:]].*[^[:alpha:]]\1[^[:alpha:]]" some-text.txt`

Q2.5) Les mots répétés deux fois sur la même ligne (seulement les mots) :

`grep -E "[^[:alpha:]]([[:alpha:]]+)[^[:alpha:]].*[^[:alpha:]]\1[^[:alpha:]]" some-text.txt -o | grep -E
"^[^[:alpha:]][[:alpha:]]+" -o | grep -E "[[:alpha:]]+" -o`

## Exercice 3

Q3.1) Toutes les lignes avec le texte laurel :

`grep -E "laurel" passwd`

Q3.2) Toutes les lignes avec le mot laurel :
`grep -E "[^[:alpha:]]laurel[^[:alpha:]]" passwd`

Q3.3) Toutes les lignes avec une adresse email (Le vrai format d’une adresse-mail est bien plus compliqué) :
`grep -E "[-\.+[:alnum:]]+@[-[:alnum:]]+\.[[:alpha:]]+" passwd`

Q3.4) Toutes les adresses email uniquement :

`grep -E "[-\.+[:alnum:]]+@[-[:alnum:]]+\.[[:alpha:]]+" passwd -o`

Q3.5) Toutes les lignes dont le login est strictement slaurel (“:” n’est pas un métacaractère)

`grep -E "^slaurel:" passwd`

Q3.6) Toutes les lignes où l’uid contient le digit 0 : `grep -E "^([^:]+:){2}[[:digit:]]*0[[:digit:]]" passwd`

Q3.7) Toutes les lignes où l’uid vaut 0 :

`grep -E "^([^:]+:){2}0:" passwd`

Q3.8) Toutes les lignes où le gid vaut 65534 :

`grep -E "^([^:]+:){3}65534:" passwd`

Q3.9) Toutes les lignes où le login shell est bash :

`grep -E "^([^:]+:){6}.*/bash" passwd`

Q3.10) Toutes les lignes où le home directory est /usr/sbin :

`grep -E "^([^:]+:){5}/usr/sbin:" passwd`

Q3.11) Toutes les lignes où le login fait exactement 4 lettres :

`grep -E "^[[:alpha:]]{4}:" passwd`

Q3.12) Toutes les lignes où le login fait au moins 4 lettres (Ici on permet à la suite de ne pas être forcément des lettres. Pour empêcher ça il faut rajouter “:”) :

`grep -E "^[[:alpha:]]{4,}" passwd`

Q3.13) Toutes les lignes où le home directory est dans /home :

`grep -E "^([^:]+:){5}/home/.*:" passwd`


