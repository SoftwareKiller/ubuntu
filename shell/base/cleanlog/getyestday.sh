#!/bin/bash

yestday=0
os_name=$(uname -s)

if [[ "$os_name" == "Linux" ]]; then
    yestday=$(date +%Y%m%d --date='-1 day')
elif [[ "$os_name"=="Darwin" ]]; then
    yestday=$(date -v -1d +%Y%m%d)
fi

echo $yestday

