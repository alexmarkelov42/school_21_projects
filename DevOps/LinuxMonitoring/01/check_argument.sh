#!/bin/bash

err=0
if [[ $1 == ?(-)+([0-9])?(.)*([0-9]) ]]
then
    err=1
fi
exit $err
