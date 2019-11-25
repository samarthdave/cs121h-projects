#include <vector>
#include <sstream>

#include "Car.hpp"

using namespace std;

// Constructor for Car
// initialize with id and # of floors
Car::Car(int i, int f) {
  cout << "car constructor: " << i << " and " << f << endl;
  this->id = i;
  this->floor = 0; // starts at the ground level
  this->nfloors = f;
  // initialize w/ state, dir & buttons
  this->state = Car::IDLE;
  this->dir = UP; // 0 is down, 1 is up (Person.hpp)
  this->buttons.push_back(0);
  this->buttons.push_back(0);
}

// static member (is the next move within bounds of building?)
bool Car::withinRange(int floor, int move, int nfloors) {
  int finalLoc = floor + move;
  return (finalLoc >= 0 && finalLoc < nfloors);
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
  int personCount = this->persons.size();
  ss << "CAR" << (this->id) << "[" << personCount << "]";
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

  cout << " " << ss.str();
}

// the most difficult part of this lab
// does everything...
void Car::update(vector<Floor> &floors, int iter, vector<Person> &allpersons) {
  // todo:
  // [x] move elevator passively up when up
  // [ ] move car up & down
  // default direction
  int moveDirection = 1;
  

  // update state for direction
  if (moveDirection != 0) {
    this->state = MOVING;
  }
//   add a +/- direction
  if (withinRange(this->floor, moveDirection, this->nfloors))
    this->floor += moveDirection;
  else
    this->state = IDLE;
}

void Car::embark(Floor &floor, int iter, vector<Person> &allPersons) {
  // loop thru allPersons and if it hit their floor, pick them up
  for (auto p: allPersons) {
    if (p.src == floor.getID()) {
      cout << "on your floor" << endl;
    }
  }
}
// void Car::disembark(Floor &floor, int iter, vector<Person> &allPersons)