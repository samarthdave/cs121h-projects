all: polynomial

polynomial: main.o Polynomial.o
	g++ --std=c++11 -o poly main.o Polynomial.o

main.o: main.cpp
	g++ --std=c++11 -c main.cpp

Polynomial.o: Polynomial.cpp Polynomial.hpp
	g++ -c Polynomial.cpp
