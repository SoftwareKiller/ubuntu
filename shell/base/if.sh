# /bin/bash

if true
then
    echo "hello"
else
    echo "bug"
fi

if false
then
    echo "bug"
elif true
then
    echo "world"
else
    echo "bsae"
fi

