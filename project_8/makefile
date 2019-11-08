CC = g++
F1 = --std=c++11

all: iris clock

# run "./iriscorr FILENAME SPECIES" for Appliation 1

iris: iris.o Matrix.o
	$(CC) $(F1) -o iriscorr iris.o Matrix.o

iris.o: iris.cpp Matrix.hpp
	$(CC) $(F1) -c iris.cpp

# run "./HourlyRotation FILENAME" for Application
clock: clock.o Matrix.o
	$(CC) $(F1) -o HourlyRotation clock.o Matrix.o

clock.o: clock.cpp
	$(CC) $(F1) -o clock.o -c clock.cpp

# MATRIX compilation

Matrix.o: Matrix.cpp Matrix.hpp
	$(CC) $(F1) -o Matrix.o -c Matrix.cpp
