 #!/bin/bash	
DIR=original_images;
mkdir "$DIR" -p;	
i=1;
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
