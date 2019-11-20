#include <vector>

#include "Car.hpp"

using namespace std;

Car::Car(int i, int f) {
  cout << "car constructor: " << i << " and " << f << endl;
}

string Car::toString() {
  return "car to string";
}