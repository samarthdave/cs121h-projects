#include <iostream>
#include <vector>
#include <sstream>

#include "Polynomial.hpp"
#include "util.hpp"

using namespace std;

void printVector(vector<string> &pm) {
  for (int i = 0; i < pm.size(); i++)
    cout << pm[i] << endl;
}

struct Component {
  double coefficient;
  int power;
};

Polynomial::Polynomial(string input) {
  cout << "constructor: " << input << endl;
  // split input with plus signs and - signs
  vector<string> components = splitByDelimiter(input, '+');
  printVector(components);
}