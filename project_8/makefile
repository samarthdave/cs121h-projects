CC = g++
F1 = --std=c++11

all: iris

# run "./iris" for Appliation 1

iris: iris.o Matrix.o
	$(CC) $(F1) -o iriscorr iris.o Matrix.o

iris.o: iris.cpp Matrix.hpp
	$(CC) $(F1) -c iris.cpp

# MATRIX compilation

Matrix.o: Matrix.cpp Matrix.hpp
	$(CC) $(F1) -o Matrix.o -c Matrix.cpp
