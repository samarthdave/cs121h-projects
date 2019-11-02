CC = g++
F1 = --std=c++11

all: polynomial

polynomial: main.o Polynomial.o util.o
	$(CC) $(F1) -o poly main.o Polynomial.o util.o

main.o: main.cpp
	$(CC) $(F1) -c main.cpp

Polynomial.o: Polynomial.cpp Polynomial.hpp
	$(CC) $(F1) -c Polynomial.cpp

util.o: util.cpp util.hpp
	$(CC) $(F1) -c util.cpp
