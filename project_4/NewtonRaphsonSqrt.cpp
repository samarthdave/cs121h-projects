#include <iostream>
#include <string> // stod, stoi, etc.
#include <cmath> // sqrt, fabs

using namespace std;

// signatures (or prototypes)
double f_prime(double);
double quadraticValueAt(double, double);
double get_intersection(double, double);
double newtonRaphsonSquareRootIterative(double);
double newtonRaphsonSquareRootRecursive(double, double, int);
bool accurateEnough(double, double, double);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Error: Enter a float after as input to estimate the square root." << endl;
    exit(1);
  }

  double squaredValue = stod(argv[1]);
  cout << "You entered " << squaredValue << endl;

  // [x] validate input (if negative)
  if (squaredValue < 0) {
    cerr << "Error: Enter a valid input above 0" << endl;
    exit(1);
  }

  // [x] iterative solution
  double newtonIterativeGuess = newtonRaphsonSquareRootIterative(squaredValue);
  // [x] recursive solution
  double recursiveGuess = squaredValue / 2;
  int recursiveIteration = 0;
  double newtonRecursive = newtonRaphsonSquareRootRecursive(squaredValue, recursiveGuess, recursiveIteration);
  // [x] built in solution
  cout << "--------------------" << endl;
  double builtInSquaredRoot = sqrt(squaredValue);
  string builtInString = "[built-in] sqrt(" + to_string(squaredValue) + ") = " + to_string(builtInSquaredRoot);
  cout << builtInString << endl;
  // [ ] verify your solution
  cout << "--------------------" << endl;
  cout << "[verify] iterative (" << newtonIterativeGuess << "^2): "
      << newtonIterativeGuess * newtonIterativeGuess << endl;
  cout << "[verify] recursive (" << newtonRecursive << "^2): "
      << newtonRecursive * newtonRecursive << endl;
}

double newtonRaphsonSquareRootIterative(double input) {
  double guess = input / 2;
  // input --> 16
  // equation = x^2 - 16
  int overflowFallback = 1;
  double tangentValue = 0.0;
  // its reasonable to assume that the value should converge in 100 runs
  while (overflowFallback <= 100) {
    // get intersection of the tangent with the x axis (when y = 0)
    tangentValue = f_prime(guess);
    
    // if the tangent is 0, we won't divide by 0!
    if (tangentValue == 0) {
      guess = 0;
      break;
    }
    // else make a guess
    guess = (-1 * quadraticValueAt(input, guess)/tangentValue) + guess;
    
    // if accurate enough
    if (accurateEnough(input, guess * guess, 0.0000001)) {
      break;
    }
    overflowFallback += 1;
  }
  return guess;
}

double newtonRaphsonSquareRootRecursive(double start, double guess, int overflow=0) {
  // threshold of accuracy
  cout << "recursive estimate " << guess << endl;
  if (overflow >= 50) {
    cout << "Preventing segmentation fault. Guess (recursive): " << guess << endl;
    return guess;
  }
  if (fabs(guess * guess - start) < 0.0000001) {
    return guess;
  }
  return newtonRaphsonSquareRootRecursive(start, 0.5 * (guess + start / guess), overflow + 1);
}


// I only made these functions for better semantics...
// derivative func.
double f_prime(double x1) {
  return 2 * x1;
}

// could be a one liner but for readability
// what is the y value at x^2 - input?
double quadraticValueAt(double input, double x1) {
  return x1 * x1 - input;
}

// check if value squared 
bool accurateEnough(double v1, double v2, double percentAccuracy) {
  double decimal = percentAccuracy / 100;
  // is the abs difference between v1 & v2 enough?
  return fabs(v1 - v2) < (decimal * v1);
}