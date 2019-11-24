#include <vector>
#include <sstream>

#include "Car.hpp"

using namespace std;

// Constructor for Car
// initialize with id and # of floors
// initilize state, dir, and buttons
Car::Car(int i, int f) {
  cout << "car constructor: " << i << " and " << f << endl;
}

// toString returns car information (eg. "CAR0[3]^")
// car num + floor + direction
string Car::toString() {
  stringstream ss;
  // car number
  ss << "CAR" << (this->id) << "[" << (this->floor) << "]";
  // car direction
  // check state and add direction if needed
  switch (this->state) {
    case Car::MOVING:
      ss << ((this->dir == 0) ? "v" : "^"); // 0 is down, 1 is up
    case Car::IDLE:
      // hit default case
      // ss << "*";
    default:
      ss << "*";
      break;
  }

  return ss.str();
}

// print cout
void Car::printSymbolic() {
  cout << this->toString();
}

// void Car::update(vector<Floor> & floors, int iter, vector<Person> & allpersons);
// void Car::embark(Floor & floor, int iter);
// void Car::disembark(Floor floor, int iter, vector<Person> & allpersons);