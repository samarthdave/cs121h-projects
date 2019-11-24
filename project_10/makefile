CC = g++
F1 = --std=c++11

all: elevator move

elevator: main.o Building.o Floor.o Car.o Person.o
	$(CC) $(F1) -o elevator main.o Building.o Floor.o Car.o Person.o

main.o: main.cpp Building.hpp
	$(CC) $(F1) -c main.cpp

Building.o: Building.cpp Building.hpp
	$(CC) $(F1) -c Building.cpp

Floor.o: Floor.cpp Floor.hpp
	$(CC) $(F1) -c Floor.cpp

Car.o: Car.cpp Car.hpp
	$(CC) $(F1) -c Car.cpp

Person.o: Person.cpp Person.hpp
	$(CC) $(F1) -c Person.cpp

move:
	mkdir -p build
	mv *.o ./build
	mv elevator ./build
	@echo "--------------------------"
	@echo 'type "make run" to execute'
	@echo "--------------------------"

run:
	./build/elevator

# phony assumes the file is always out of date
.PHONY: clean
clean:
	rm *.o