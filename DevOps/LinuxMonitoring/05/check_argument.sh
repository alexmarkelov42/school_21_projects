#!/bin/bash
# 0 - OK
# 1 - incorrect number of args
# 2 - incorrect path to directory

err=0
if [[ $# != 1 ]]
then
    err=1
    exit $err
elif [[ -d $1 ]] && [[ ${1: -1} == / ]]
then
    err=0
    exit $err
else
    err=2
    exit $err
fi

    
