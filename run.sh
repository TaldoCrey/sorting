#!/bin/bash
if [ -n $1 ]; then
    if [ "$1" == "-t" ]; then
        echo "Running test"
        ./builds/test
    else
        echo "Running main.cpp"
        ./builds/app
    fi
else
    echo "Running main.cpp"
    ./builds/app
fi