all: genomics

genomics: genomics.o codons.o
	g++ -o genomics genomics.o codons.o


genomics.o: genomics.cpp codons.hpp
	g++ --std=c++11 -c genomics.cpp


codons.o: codons.cpp codons.hpp
	g++ -c codons.cpp
