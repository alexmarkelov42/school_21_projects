#!/bin/bash

function send_notification() {
    TEXT="stage - unit_test. Status - $status"
    curl -s -X POST -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
    #echo $TEXT
}

TELEGRAM_BOT_TOKEN=6122597388:AAFRwhwLMM6DM5NZ416syI7HO9uhfgdCj9g
TELEGRAM_USER_ID=386851623

status="success"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

cp ./artifacts/s21_cat ./src/cat/
cp ./artifacts/s21_grep ./src/grep/
cd ./src/cat
./test_cat_jarrusab.sh
if [[ $? != 0 ]];
then
    status="failed"
    send_notification
    exit 1
fi
cd ../grep
./test_grep_jarrusab.sh
if [[ $? != 0 ]];
then
    status="failed"
    send_notification
    exit 1
fi
send_notification
