CC = g++
F1 = --std=c++11

all: elevator

elevator: build/main.o build/Container.o build/Building.o build/Floor.o build/Car.o build/Person.o
	$(CC) $(F1) -o ./build/$@ $^

build/main.o: main.cpp Building.hpp
	$(CC) $(F1) -c main.cpp -o $@

build/Container.o: Container.cpp Container.hpp
	$(CC) $(F1) -c Container.cpp -o $@

build/Building.o: Building.cpp Building.hpp
	$(CC) $(F1) -c Building.cpp -o $@

build/Floor.o: Floor.cpp Floor.hpp
	$(CC) $(F1) -c Floor.cpp -o $@

build/Car.o: Car.cpp Car.hpp
	$(CC) $(F1) -c Car.cpp -o $@

build/Person.o: Person.cpp Person.hpp
	$(CC) $(F1) -c Person.cpp -o $@

run:
	@echo "Running elevator:"
	./build/elevator 100 5 1 tests/traffic_5_100_0.5.txt

# phony assumes the file is always out of date
.PHONY: clean
clean:
	rm build/*