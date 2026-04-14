#!/bin/bash
if [ -n "$1" ]; then
	if [ "$1" == "--test-alg" ]; then
		g++ ./tests/test_a.cpp -o ./builds/test
		echo "Compiled algorithm test with success"
	elif [ "$1" == "--test-str" ]; then
		g++ ./tests/test_s.cpp -o ./builds/test
		echo "Compiled structure test with success"
	else
		g++ main.cpp -o ./builds/app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -utf-8
		echo "Compiled with success"
	fi
else
	g++ main.cpp -o ./builds/app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -utf-8
	echo "Compiled with success"
fi
