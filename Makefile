GXX=g++ -march=native -std=c++11

all: main

main: Snake.cpp Settings.o
	${GXX} -o Snake.exe Snake.cpp Settings.o

Settings.o: Settings.h Settings.cpp
	${GXX} -c -o Settings.o Settings.cpp
