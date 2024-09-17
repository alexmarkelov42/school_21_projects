#!/bin/bash

declare -A txt_color
declare -A bg_color

txt_color["1"]="37" #White
txt_color["2"]="31" #Red
txt_color["3"]="32" #Green
txt_color["4"]="34" #Blue
txt_color["5"]="35" #Purple
txt_color["6"]="30" #Black

bg_color["1"]="47" #White
bg_color["2"]="41" #Red
bg_color["3"]="42" #Green
bg_color["4"]="44" #Blue
bg_color["5"]="45" #Purple
bg_color["6"]="40" #Black

end="\e[0m" # reset coloring

memtotal=$(cat /proc/meminfo | awk '$1 == "MemTotal:" {printf("%.3f", $2 * 0.000001); exit}')
memfree=$(cat /proc/meminfo | awk '$1 == "MemAvailable:" {printf("%.3f", $2 * 0.000001); exit}')

col1_color="\033[${bg_color[$1]};${txt_color[$2]}m"
col2_color="\033[${bg_color[$3]};${txt_color[$4]}m"

echo -e "${col1_color}HOSTNAME$end=${col2_color}$(hostname)$end"
echo -e "${col1_color}TIMEZONE$end=${col2_color}$(cat /etc/timezone) $(date +"%z")$end"
echo -e "${col1_color}USER$end=${col2_color}$USER$end"
echo -e "${col1_color}OS$end=${col2_color}$(uname -o) $(uname -r)$end"
echo -e "${col1_color}DATE$end=${col2_color}$(date +"%d %b %Y %T")$end"
echo -e "${col1_color}UPTIME$end=${col2_color}$(uptime -p)$end"
echo -e "${col1_color}UPTIME_SEC$end=${col2_color}$(cat /proc/uptime | cut -d ' ' -f 1)$end"
echo -e "${col1_color}IP=${col2_color}$(ifconfig | grep netmask | awk '{print $2; exit}')$end"
echo -e "${col1_color}MASK$end=${col2_color}$(ifconfig | grep netmask | awk '{print $4; exit}')$end"
echo -e "${col1_color}GATEWAY$end=${col2_color}$(ip r | grep default | awk '{print $3; exit}')$end"
echo -e "${col1_color}RAM_TOTAL$end=${col2_color}$memtotal GB$end"
echo -e "${col1_color}RAM_USED$end=${col2_color}$(echo $memtotal $memfree | awk '{print $1 - $2}') GB$end"
echo -e "${col1_color}RAM_FREE$end=${col2_color}$memfree GB$end"
echo -e "${col1_color}SPACE_ROOT$end=${col2_color}$(df -B1 / | awk 'NR > 1 {printf("%.3f MB", $2 / 1000000); exit}')$end"
echo -e "${col1_color}SPACE_ROOT_USED$end=${col2_color}$(df -B1 / | awk 'NR > 1 {printf("%.3f MB", $3 / 1000000); exit}')$end"
echo -e "${col1_color}SPACE_ROOT_FREE$end=${col2_color}$(df -B1 / | awk 'NR > 1 {printf("%.3f MB", $4 / 1000000); exit}')$end"
