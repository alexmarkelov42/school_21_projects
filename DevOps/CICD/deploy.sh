#!/bin/bash

function send_notification() {
    TEXT="stage - deploy. Status - $status"
    curl -s -X POST -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
    #echo $TEXT
}

TELEGRAM_BOT_TOKEN=6122597388:AAFRwhwLMM6DM5NZ416syI7HO9uhfgdCj9g
TELEGRAM_USER_ID=386851623

status="success"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

scp -P 2222 -B -i /home/olex/.ssh/id_rsa -v -o StrictHostKeyChecking=no ./artifacts/s21_cat ./artifacts/s21_grep olex@192.168.1.222://tmp
if [[ $? == 0 ]];
then
    echo "copied files to deploy machine"
else
    status="failed"
    send_notification
    exit 1
fi

ssh -p 2222 olex@192.168.1.222 sudo mv /tmp/s21_grep /tmp/s21_cat /usr/local/bin

if [[ $? == 0 ]];
then
    echo "ssh-ed to a deploy machine"
else
    status="failed"
    send_notification
    exit 1
fi

send_notification
