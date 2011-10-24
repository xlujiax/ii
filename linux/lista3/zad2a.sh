#!/bin/bash
FILE=`zcat $1 | grep Googlebot | grep -o "\([0-9]*\.[0-9]*\.[0-9]*\.[0-9]*\)"`

declare -A hash

for ip in `echo $FILE | sort | uniq`
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