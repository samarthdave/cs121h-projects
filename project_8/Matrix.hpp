// --------------------
//      Matrix.hpp
// --------------------

#include <iostream>

using namespace std;

#ifndef Matrix_hpp
#define Matrix_hpp

class Matrix {
// PRIVATE members
protected:
  double ** heapArray;
  int P; // rows
  int Q; // columns

  // validate input
  bool isValidLoc(int, int);

// PUBLIC members
public:
  // constructors
  Matrix(int, int);
  Matrix(const Matrix &);
  
  // custom operators
  Matrix operator*(Matrix &);
  Matrix transpose();
  string toString(); // toString using sstream
  void print(); // uses toString method

  // getters & setters
  float get(int, int);
  void set(int, int, float);
  // get dimensions
  int getNumRows();
  int getNumCols();
  
};

#endif // Matrix_hpp