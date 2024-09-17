#!/bin/bash
dir=$(dirname $0)
$dir/check_params.sh $@
error=$?
if [ $error == 1 ]
then
    echo "Error. 4 Arguments required"
elif [ $error == 2 ]
then
    echo "Error. Font color and BG color are the same"
elif [ $error == 3 ]
then
    echo "Error. Argument must be 1-6"
else
    $dir/print_inf.sh $@
fi

exit 0
