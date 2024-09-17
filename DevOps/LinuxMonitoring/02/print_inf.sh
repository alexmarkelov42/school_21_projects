#!/bin/bash

echo "HOSTNAME=$(hostname)"
echo "TIMEZONE=$(cat /etc/timezone) $(date +"%z")"
echo "USER=$USER"
echo "OS=$(uname -o) $(uname -r)"
echo "DATE=$(date +"%d %b %Y %T")"
echo "UPTIME=$(uptime -p)"
echo "UPTIME_SEC=$(cat /proc/uptime | cut -d ' ' -f 1)"
echo "IP=$(ifconfig | grep netmask | awk '{print $2; exit}')"
echo "MASK=$(ifconfig | grep netmask | awk '{print $4; exit}')"
echo "GATEWAY=$(ip r | grep default | awk '{print $3; exit}')"
memtotal=$(cat /proc/meminfo | awk '$1 == "MemTotal:" {printf("%.3f", $2 * 0.000001); exit}')
memfree=$(cat /proc/meminfo | awk '$1 == "MemAvailable:" {printf("%.3f", $2 * 0.000001); exit}')
echo "RAM_TOTAL=$memtotal GB"
echo "RAM_USED=$(echo $memtotal $memfree | awk '{print $1 - $2}') GB"
echo "RAM_FREE=$memfree GB"
echo "SPACE_ROOT=$(df -B1 / | awk 'NR > 1 {printf("%.2f MB", $2 / 1000000); exit}')"
echo "SPACE_ROOT_USED=$(df -B1 / | awk 'NR > 1 {printf("%.2f MB", $3 / 1000000); exit}')"
echo "SPACE_ROOT_FREE=$(df -B1 / | awk 'NR > 1 {printf("%.2f MB", $4 / 1000000); exit}')"

