#!/bin/bash
FILE=`zcat $1 | grep "GET /.* HTTP/1.1\" 200" | grep -o "\[.*\]" | grep -o ":..:"`

declare -A hash

for ip in `echo $FILE`
do
    lookup=`echo ${hash[$ip]}`
    if [ -z $lookup ]
    then
	hash[$ip]="1"
    else
	hash[$ip]=`expr 1 + $lookup`
    fi
done

for h in "${!hash[@]}"
do
    echo "$h - ${hash["$h"]}";
done