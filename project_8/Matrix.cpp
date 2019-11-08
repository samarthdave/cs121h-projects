#include <iostream>
#include <sstream>
#include <iomanip> // setprecision

#include "Matrix.hpp"

using namespace std;

// CONSTRUCTOR 1
Matrix::Matrix(int a, int b) {
  P = a;
  Q = b;

  heapArray = new double*[P];
  for (int i = 0; i < P; ++i) {
    heapArray[i] = new double[Q];
  }

  // initialize all values to 0
  for (int i = 0; i < P; i++)
    for (int j = 0; j < Q; j++)
      heapArray[i][j] = 0.0;
}

// CONSTRUCTOR 2 - copy constructor
Matrix::Matrix(const Matrix &p) {
  // loop thru both & make a copy
  heapArray = new double*[P];
  for (int i = 0; i < P; ++i) {
    heapArray[i] = new double[Q];
  }
  
  // set new heap values to old values
  for (int i = 0; i < P; i++)
    for (int j = 0; j < Q; j++)
      heapArray[i][j] = p.heapArray[i][j];
}

// get locaiton in grid
float Matrix::get(int row, int col) {
  if (!isValidLoc(row, col)) {
    exit(1);
    return -1.0;
  }
  // now loop through and find it
  return heapArray[row][col];
}

// set location in grid
void Matrix::set(int row, int col, float val) {
  if (!isValidLoc(row, col)) {
    cerr << "Invalid row or column: " << row << "x" << col << endl;
    exit(1);
    return;
  }
  // set the value
  heapArray[row][col] = val;
}

// MATRIX multiplication
// overload multiply operator
Matrix Matrix::operator*(Matrix &g) {
  // validate dimensions of both matricies
  // col of this should equal rows of g
  if (this->Q != g.P) {
    cerr << "Error: Cannot multiply these matricies of invalid dimensions." << endl;
    cerr << "A: " << P << "x" << Q << " and B: " << g.P << "x" << g.Q << endl;
    exit(1);
  }

  Matrix productMatrix = { this->P, g.Q };

  int i, j, k;
  for (i = 0; i < this->P; i++) {
    for (j = 0; j < g.Q; j++) {
      productMatrix.heapArray[i][j] = 0.0;
      for (k = 0; k < g.P; k++)
        productMatrix.heapArray[i][j] += (heapArray[i][k] * g.heapArray[k][j]);
    }
  }

  return productMatrix;
} // operator *

// TRANSPOSE the matrix
// rows become cols and vice versa
Matrix Matrix::transpose() {
  Matrix p = { Q, P };

  int i, j;
  for (i = 0; i < P; i++)
    for (j = 0; j < Q; j++)
      p.heapArray[j][i] = heapArray[i][j];

  return p;
}

// toString matrix
string Matrix::toString() {
  stringstream ss;
  
  for (int i = 0; i < P; i++) {
    for (int j = 0; j < Q; j++) {
      // trim down to 3 decimal accuracy
      ss << setw(6) << setprecision(3) << heapArray[i][j] << ' ';
    }
    // if not last line, print new line
    ss << ((i == P-1) ? "" : "\n");
  }

  return ss.str();
}

// make it pretty
void Matrix::print() {
  cout << "Matrix: " << '[' << endl;
  cout << this->toString() << endl;
  cout << ']' << endl;
}

// MATRIX validation
// is valid row, col
bool Matrix::isValidLoc(int row, int col) {
  // if too small
  if (row < 0 || col < 0) {
    cerr << "Invalid input. R: " << row << " & C: " << col << '.' << endl;
    cerr << "P: " << P << " & Q: " << Q << endl;
    return false;
  }
  // if too big
  if (row >= P || col >= Q) {
    cerr << "Invalid input. R: " << row << " & C: " << col << '.' << endl;
    cerr << "P: " << P << " & Q: " << Q << endl;
    return false;
  }

  return true;
}

int Matrix::getNumRows() {
  return this->P;
}

int Matrix::getNumCols() {
  return this->Q;
}