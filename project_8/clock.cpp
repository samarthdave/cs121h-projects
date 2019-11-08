#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath> // sqrt, sin, cos
#include <string> // stod

#include "Matrix.hpp"

#define PI 3.141592653589793

using namespace std;

class Point2D : public Matrix {
// public members
public:
  Point2D() : Matrix(1, 2) { /* */ }
  Point2D(double x, double y) : Matrix(1, 2) {
    set(0,0, x);
    set(0,1, y);
  }
};

class Rot2D : public Matrix {
// public members
public:
  Rot2D(double thetaDegrees) : Matrix(2, 2) {
    double rad = thetaDegrees * 3.141592653589793 / 180.0;

    // primitive rounding to 3 decimal places
    // this is for trig functions that give very small doubles instead of 0
    int places = 10000;
    // round values
    double a00 = round(cos(rad) * places) / places;
    double a01 = round(-sin(rad) * places) / places;
    double a10 = round(sin(rad) * places) / places;
    double a11 = round(cos(rad) * places) / places;

    set(0,0, a00);
    set(0,1, a01);
    set(1,0, a10);
    set(1,1, a11);
  }
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

  // tracker variables
  int lineCount = 0;
  double a, b;

  // number vectors
  vector<double> first;
  vector<double> second;

  while (fin >> a >> b) {
    first.push_back(a);
    second.push_back(b);
  }

  int N = first.size();

  Point2D points[N];
  for (int i = 0; i < N; i++) {
    points[i] = Point2D(first[i], second[i]);
  }

  // ------------------------------
  // initialize identity matricices
  //   (just for fun)
  // ------------------------------
  // A - 30 deg:
  // 0.866 -0.500
  // 0.500 0.866
  Rot2D A = { 30 };
  // B - 60 deg:
  // Rot2D B = { 60 };
  // C - 90 deg:
  // Rot2D C = { 90 };
  // D
  // Rot2D D = { -60 };

  int HOURS = 12;

  // hour 0 is no rotation...hence starting at 1
  for (int i = 1; i <= HOURS; i++) {
    cout << "Hour " << i << endl;
    for (int j = 0; j < N; j++) {
      // multiply each point by an angle of 30 times the iteration
      Rot2D angle = Rot2D(30*i);

      double c11 = points[j].get(0,0) * angle.get(0,0) + points[j].get(0,1) * angle.get(1,0);
      double c22 = points[j].get(0,0) * angle.get(0,1) + points[j].get(0,1) * angle.get(1,1);
      Point2D prod = Point2D(c11, c22);

      cout << prod.toString() << endl;
    }
    // conditional line
    if (i != HOURS) cout << "-------------" << endl;
  }
  cout << "-------------------------------" << endl;

}
