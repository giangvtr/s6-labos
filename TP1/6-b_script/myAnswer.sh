#!/bin/bash
echo "Give your text (When finish type Ctrl+D) !"

#arr is now the array that holds our arguments
readarray -t arr 


echo -e  "Your text is :\n"
echo "${arr[*]}"
