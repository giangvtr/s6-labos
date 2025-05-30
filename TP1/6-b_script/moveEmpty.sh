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
