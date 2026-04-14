#!/bin/bash
if [ -n $1 ]; then
    if [ "$1" == "-l" ]; then
        echo "Compiling LINUX release"
        g++ -O3 -s main.cpp -o ./lin-release/Sorting -Llibs/linux -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,'$ORIGIN/libs/linux'
        echo "Compreesing linux release"
        tar -czvf sorting-gui.tar.gz -C ./lin-release .
    elif [ "$1" == "-w" ]; then
        echo "Compiling WINDOWS release"
        x86_64-w64-mingw32-g++ -O3 -s main.cpp -o "./win-release/Sorting.exe" -Ilibs/windows/include -Llibs/windows -lsfml-graphics -lsfml-window -lsfml-system -mwindows
        echo "Compressing windows release"
        cd win-release && zip -r ../sorting-gui-win.zip . && cd ..
    else 
        echo "Escolha uma flag para compilação: -l para LINUX | -w para WINDOWS"
    fi
fi