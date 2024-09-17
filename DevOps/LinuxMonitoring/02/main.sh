#!/bin/bash
dir=$(dirname $0)
tmpname=$(mktemp -p $dir )
$dir/print_inf.sh | tee $tmpname;
echo "Save to file? Y/N"
read answer
if [[ $answer == +([Y,y]) ]]
then
    $dir/save_to_file.sh $tmpname
else
    rm $tmpname
fi





