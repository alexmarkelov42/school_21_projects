#!/bin/bash
# 0 - OK
# 1 - incorrect number of arguments
# 2 - incorrect argument
# 3 - bg and font color are the same
err=0

if [ $# != 4 ]
then
    err=1
    exit $err
fi

if [ $1 == $2  ] || [ $3 == $4  ]
then
    err=2
    exit $err
fi

for arg in $@
do
    if [[ $arg != @([1-6]) ]]
    then
	err=3
	exit $err
    fi
done

exit 0
