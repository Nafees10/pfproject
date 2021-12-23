#!/bin/sh
(cd bin && g++ -c ../src/*.cpp) && g++ bin/*.o -o bin/pfproject -lsfml-graphics -lsfml-window -lsfml-system
