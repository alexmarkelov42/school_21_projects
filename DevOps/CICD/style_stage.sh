#!/bin/bash

function send_notification() {
    TEXT="stage - style_test. Status - $status"
    curl -s -X POST -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
    #echo $TEXT
}

TELEGRAM_BOT_TOKEN=6122597388:AAFRwhwLMM6DM5NZ416syI7HO9uhfgdCj9g
TELEGRAM_USER_ID=386851623

status="success"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

cd ./src/cat
cp ../../materials/linters/.clang-format .
clang-format -Werror -n *.c *.h
if [[ $? != 0 ]];
then
    status="failed"
    send_notification
    rm .clang-format
    exit 1
fi
rm .clang-format

cd ../grep/
cp ../../materials/linters/.clang-format .
clang-format -Werror -n *.c *.h
if [[ $? != 0 ]];
then
    status="failed"
    rm .clang-format
    send_notification
    exit 1
fi
rm .clang-format
send_notification
