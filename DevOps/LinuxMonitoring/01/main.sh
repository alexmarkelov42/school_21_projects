#!/bin/bash
dir=$(dirname $0)
nil=0
if [ $# -ne 1 ]
then
    echo "wrong number of arguments"
else
    $dir/check_argument.sh $1
    if [ $? -eq 0 ]
    then
	echo "$1"
    else
	echo "Error. Argument is a number"
    fi
fi
    
