#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath> // sqrt

#include "Matrix.hpp"

using namespace std;

class Point2D : public Matrix {
// public members
public:
  Point2D(double x, double y) : Matrix(1, 2) {
  }
};

class Rot2D : public Matrix {
// public members
public:
  Rot2D() : Matrix(2, 2) { /* */ }
};

// usage: "./HourlyRotation FILENAME SPECIES"
int main(int argv, char *argc[]) {

  cout << "-------------------------------" << endl;
  cout << "Project 8: Application 2 - Rotating Geometrical Objects" << endl;
  cout << "-------------------------------" << endl;
  
  if (argv != 2) {
    cout << "ERROR, invalid input. Usage: \"./HourlyRotation FILENAME \"" << endl;
    exit(1);
  }
  
  // read command line args
  string filename = argc[1];

  // read text file
  ifstream fin;
  fin.open(filename);

  if(!fin.is_open()) {
    cout << "ERROR: Cannot open input file." << endl;
    exit(1);
  }

  // initialize trackers
  int LINE_COUNT = 0;
  string line = "";

  // get lines from the file
  while (getline(fin, line)) {
    LINE_COUNT += 1;

    // convert to stream so getline works
    stringstream stream(line);
    
    string data[2] = { "" }; // sets all values in array to ""
    int i = 0;
    //loop to split string
    while(getline(stream, data[i])) {
      //increase repetition number
      i++;
    }

  }

}
