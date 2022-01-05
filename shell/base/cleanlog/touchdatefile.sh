#!/bin/bash

minus='-'
d='d'
for((i=1; i<=10; i++))
do
    num='$i'
    args=$minus$i$d
    file=$(date -v $args +%Y%m%d)
    touch $file
done

