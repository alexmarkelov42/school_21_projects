#!/bin/bash

function send_notification() {
    TEXT="stage - build. Status - $status"
    curl -s -X POST -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
    #echo $TEXT
}

TELEGRAM_BOT_TOKEN=6122597388:AAFRwhwLMM6DM5NZ416syI7HO9uhfgdCj9g
TELEGRAM_USER_ID=386851623

status="success"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

start_text="starting pipeline on branch $CI_COMMIT_BRANCH , last commit $CI_COMMIT_SHORT_SHA, $CI_COMMIT_MESSAGE"

curl -s -X POST -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$start_text" $URL > /dev/null

mkdir artifacts
cd ./src/cat
make all
if [ $? -ne 0 ];
then
    status="failed"
    send_notification
    exit 1
fi
cp s21_cat ../../artifacts
cd ../grep/
make all
if [ $? -ne 0 ];
then
    status="failed"
    send_notification
    exit 1
fi
cp s21_grep ../../artifacts
send_notification
