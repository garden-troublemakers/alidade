#!/bin/bash
mkdir -p bin
echo "G. Albespy, G. Breda, T. Gay, A. Mahé"
echo "Compiling our Portal version : alidade, this will take some time"
g++ src/*.cpp stein/*.cpp stein/glew/*.c -I. -lGL -lSDL -O3 -Wall -o bin/alidade
echo "done ! Now go in the bin directory and launch ./alidade"
