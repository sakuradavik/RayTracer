all: main

main: main.o vector.o
	g++ main.o -o main -lGL -lGLU -lglut -lm

main.o: main.cpp
	g++ -c main.cpp 

vector.o: Vectors.cpp Vectors.h
	g++ -c Vectors.cpp

clean:
	rm -rf *o main
