CC = g++
F1 = --std=c++11

all: elevator move

elevator: main.o Container.o Building.o Floor.o Car.o Person.o
	$(CC) $(F1) -o elevator main.o Container.o Building.o Floor.o Car.o Person.o

main.o: main.cpp Building.hpp
	$(CC) $(F1) -c main.cpp

Container.o: Container.cpp Container.hpp
	$(CC) $(F1) -c Container.cpp

Building.o: Building.cpp Building.hpp
	$(CC) $(F1) -c Building.cpp

Floor.o: Floor.cpp Floor.hpp
	$(CC) $(F1) -c Floor.cpp

Car.o: Car.cpp Car.hpp
	$(CC) $(F1) -c Car.cpp

Person.o: Person.cpp Person.hpp
	$(CC) $(F1) -c Person.cpp

move:
	@echo "--------------------------"
	@echo "Moving files from working"
	@echo "directory to ./build/"
	@echo "--------------------------"
	mkdir -p build
	mv *.o ./build
	mv elevator ./build
	@echo "--------------------------"
	@echo 'type "make run" to execute'
	@echo "or use './build/elevator'"
	@echo "--------------------------"

run:
	./build/elevator 10 5 1 tests/easyTest.txt

# phony assumes the file is always out of date
.PHONY: clean
clean:
	rm *.o