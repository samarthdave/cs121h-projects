all: polynomial

polynomial: main.o Polynomial.o util.o
	g++ --std=c++11 -o poly main.o Polynomial.o util.o

main.o: main.cpp
	g++ --std=c++11 -c main.cpp

Polynomial.o: Polynomial.cpp Polynomial.hpp
	g++ --std=c++11 -c Polynomial.cpp

util.o: util.cpp util.hpp
	g++ --std=c++11 -c util.cpp
