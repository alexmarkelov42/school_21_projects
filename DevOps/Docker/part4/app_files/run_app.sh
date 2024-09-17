#!/bin/bash

gcc hello_fcgi.c -o hello_fcgi.out -lfcgi &&
    spawn-fcgi -a 0.0.0.0 -p 8081 hello_fcgi.out
nginx &
while true; do sleep 1000; done
