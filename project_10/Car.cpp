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

// printSymbolic returns car information (eg. "CAR0[3]^")
// car num + floor + direction
void Car::printSymbolic() {
  stringstream ss;
  // car number
  ss << "CAR" << (this->id) << "[" << (this->floor) << "]";
  // car direction
  // check state and add direction if needed
  switch (this->state) {
    case Car::MOVING:
      // 0 is down, 1 is up
      ss << ( (this->dir == 0) ? "v" : "^" );
    case Car::IDLE:
      // hit default case
      // ss << "*";
    default:
      ss << "*";
      break;
  }

  cout << "SYMBOLIC: " << ss.str() << endl;;
}

// void Car::update(vector<Floor> & floors, int iter, vector<Person> & allpersons);
// void Car::embark(Floor & floor, int iter);
// void Car::disembark(Floor floor, int iter, vector<Person> & allpersons);