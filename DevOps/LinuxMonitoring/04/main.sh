#!/bin/bash
dir=$(dirname $0)
colors=(1 5 2 5) #default color scheme
default=0
for (( i = 0; i <= 3; i++ ))
do
    read -r line
    if [[ "$line" == "column1_background="@([1-6]) ]];
    then
	colors[0]=${line: -1}
	default=1
    fi
    if [[ "$line" == "column1_font_color="@([1-6]) ]];
    then
	colors[1]=${line: -1}
	default=1
    fi
    if [[ "$line" == "column2_background="@([1-6]) ]];
    then
	colors[2]=${line: -1}
	default=1
    fi
    if [[ "$line" == "column2_font_color="@([1-6]) ]];
    then
	colors[3]=${line: -1}
	default=1
    fi
done < $dir/colors.conf

$dir/check_params.sh $(echo ${colors[*]})
err=$?
if [ $err == 2 ]
then
    echo "front color and background color must be different"
else
    $dir/print_inf.sh $(echo ${colors[*]}) $default
fi

exit 0
