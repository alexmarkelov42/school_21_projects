#!/bin/bash
start_time=$(date +%s.%N)
dir=$(dirname $0)
$dir/check_argument.sh $@

err=$?
if [ $err == 1 ]
then
    echo "Error. Incorrect number of arguments"
elif [ $err == 2 ]
then
    echo "Error. Invalid directory path. (path must end with /)"
else
    $dir/print_inf.sh $1    
    end_time=$(date +%s.%N)
    exec_time=$(printf "%.1f" $(echo $end_time - $start_time | bc -l))
    echo "Script execution time (in seconds) = $exec_time"
fi

