#!/bin/bash

echo "Total number of folders (including all nested ones) = $(du -c $1 | awk '$2 == "total"{print $1}')"
echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
echo "$(find $(echo "$1*") -type d -exec du -h 2>/dev/null \{\} \; | sort -hr | uniq | head -n 5 | awk '{OFS=", "; i = 1}{print NR " - " $2, $1; i = i + 1}')"
echo "Total number of files = $(find $1 -type f | wc -l)"
echo "Number of:"
echo "Configuration files (with the .conf extension) = $(find $1 -type f -iname "*.conf" | wc -l)"
echo "Text files (with the .txt extension) = $(find $1 -type f -iname "*.txt" | wc -l)"
echo "Executable files = $(find $1 -type f -executable | wc -l)"
echo "Log files (with the extension .log) = $(find $1 -type f -iname "*.txt" | wc -l)"
echo "Archive files = $(find $1 -type f | grep -e .zip -e .tar.gz | wc -l)"
echo "Symbolic links = $(find $1 -type l | wc -l)"
echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
readarray -t file_arr < <(find $1 -type f -exec du -h 2>/dev/null \{\} \; | sort -hr | uniq | head -n 10 )
filenames=()
filesizes=()
filetypes=()
for (( i=0; i < ${#file_arr[@]}; i+=1 ))
do
    filenames[$i]="$(echo ${file_arr[$i]} | awk '{print $2}')"
    filesizes[$i]="$(echo ${file_arr[$i]} | awk '{print $1}')"
    filetypes[$i]="$(file -bs $(echo ${file_arr[$i]} | awk '{print $2}'))"
done

for ((i=0; i < ${#file_arr[@]}; i++))
do
    echo -n $((i+1))
    echo -n " - ${filenames[$i]}"
    echo -n ", ${filesizes[$i]}"
    echo ", $(echo ${filetypes[$i]} | cut -d "," -f 1)"
done

readarray -t base_arr < <(du -h 2>/dev/null $(find $1 -type f -executable 2>/dev/null) | sort -hr | uniq | head)
filename_arr=()
filesize_arr=()
md5sum_arr=()

for (( i=0; i < ${#base_arr[@]}; i+=1 ))
do
    filename_arr[$i]="$(echo ${base_arr[$i]} | awk '{print $2}')"
    filesize_arr[$i]="$(echo ${base_arr[$i]} | awk '{print $1}')"
    md5sum_arr[$i]="$(md5sum ${filename_arr[$i]} | awk '{print $1}')"
done

echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file)"
for ((i=0; i < ${#filename_arr[@]}; i++))
do
    echo -n $((i+1))
    echo -n " - ${filename_arr[$i]}"
    echo -n ", ${filesize_arr[$i]}"
    echo ", ${md5sum_arr[$i]}"
    #printf "$((i+1)) - %s, %s, %s\n" ${filename_arr[$i]} ${filesize_arr[$i]} ${md5sum_arr[$i]}
done
