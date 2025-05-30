#!/bin/bash
i=1
script=$(basename $BASH_SOURCE)
echo "The script is : " $script 
for arg do
echo "The parameter "$i" is : "$arg
i=$((i + 1))
done
