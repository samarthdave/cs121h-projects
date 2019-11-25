#include <vector>
#include <sstream>

#include "Car.hpp"

using namespace std;

// Constructor for Car
// initialize with id and # of floors
// initilize state, dir, and buttons
Car::Car(int i, int f) {
  cout << "car constructor: " << i << " and " << f << endl;
  this->id = i;
  this->floor = 0; // starts at the ground level
  this->state = Car::IDLE;
  this->dir = UP; // 0 is down, 1 is up (Person.hpp)
  this->nfloors = f;
}

string Car::toString() {
  // CAR 0, floor 1, load 0, state 1, dir 1, buttonsPressed: 
  stringstream ss;

  ss << "CAR " << (this->id) << ", " << " floor " << (this->floor);
  ss << ", load " << (this->persons.size());
  ss << ", state " << (this->state);
  ss << ", dir " << (this->dir);

  string buttonOutput = "";
  for (int i = 0; i < this->buttons.size(); i++) {
    buttonOutput += ((this->buttons[i]) ? to_string(i) : "");
  }
  ss << ", buttonsPressed: " << buttonOutput;

  return ss.str();
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
      ss << ((this->dir == 0) ? "v" : "^" );
      break;
    case Car::IDLE:
      // hit default case
      // ss << "*";
    default:
      ss << "*";
      break;
  }

  cout << "SYMBOLIC: " << ss.str() << endl;;
}

// the most difficult part of this lab
// does everything...
// void Car::update(vector<Floor> &floors, int iter, vector<Person> & allpersons) {
  // default direction
  // int moveDirection;
  // get the direction it should move
  // if no buttons pressed AND isn't at the top, moveDirection is +
  // if (noButtonsPressed && this->floor != nfloors-1) {
    // moveDirection = 1;
  // }

  // add a +/- direction
//   this->floor += moveDirection;
// }

// void Car::embark(Floor & floor, int iter);
// void Car::disembark(Floor floor, int iter, vector<Person> & allpersons);