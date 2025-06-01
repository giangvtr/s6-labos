#!/bin/bash
if [ $# -ne 1 ]
  then
  echo "This program should have one argument" >&2
  exit 1
fi

MIN=$1
find . -type f -mmin -$MIN