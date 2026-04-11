#!/bin/bash

if [ -n "$1" ]; then
	if [["$1" != "--not-run"]]; then
		g++ $1 -o app -O2 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -utf-8 -lFLAC
	else
		g++ main.cpp -o app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -utf-8 -lFLAC
		echo "Compiled with success"
	fi
else
	g++ main.cpp -o app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -utf-8 -lFLAC
fi


