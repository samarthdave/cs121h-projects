#include <vector>
#include <sstream>

#include "Car.hpp"

using namespace std;

// Constructor for Car
// initialize with id and # of floors
Car::Car(int i, int f) {
  id = i;
  floor = 0; // starts at the ground level
  nfloors = f;
  capacity = 10;
  // initialize w/ state, dir & buttons
  state = Car::IDLE;
  dir = UP; // 0 is down, 1 is up (Person.hpp)
  for (int i = 0; i < nfloors; i++) {
    buttons.push_back(false);
  }
}

// static member (is the next move within bounds of building?)
bool Car::withinRange(int floor, int move, int nfloors) {
  int finalLoc = floor + move;
  return (finalLoc >= 0 && finalLoc < nfloors);
}

string Car::toString() {
  // CAR 0, floor 1, load 0, state 1, dir 1, buttonsPressed: 
  stringstream ss;

  ss << "CAR " << id << ", floor " << floor;
  ss << ", load " << persons.size();
  ss << ", state " << state;
  ss << ", dir " << dir;

  ss << ", buttonsPressed: ";
  for (int i = 0; i < nfloors; i++) {
    if (buttons[i])
      ss << i << ' ';
  }

  return ss.str();
}

// printSymbolic returns car information (eg. "CAR0[3]^")
void Car::printSymbolic() {
  stringstream ss;
  // car number
  int personCount = this->persons.size();
  ss << "CAR" << (this->id) << "[" << personCount << "]";
  // car direction
  char token = '*';
  if (state == MOVING) {
    if (dir == UP) { token = '^'; }
    else { token = 'v'; }
  }
  ss << token;
  cout << " " << ss.str();
}

void Car::update(vector<Floor> &f4, int iter, vector<Person> &allPersons) {
  if (floor == nfloors - 1){
    dir = DOWN;
  }
  if (floor == 0) {
    dir = UP;
  }
  bool load = false;
  bool unload = buttons[floor];

  if (dir == UP && f4[floor].UpPressed()) {
    load = true;
  }
  if (dir == DOWN && f4[floor].DownPressed()) {
    load = true;
  }
  int moveDirection = 0;
  // set direction for push size
  if (dir == UP) moveDirection = 1;
  else moveDirection = -1;
  
  if (!(unload || load)) {
    state = MOVING;
    if (withinRange(this->floor, moveDirection, this->nfloors))
      this->floor += moveDirection;
  } else {
    if (unload) {
      state = UNLOADING;
      disembark(f4[floor], iter, allPersons);
    }
    if (load) {
      state = LOADING;
      embark(f4[floor], iter);
    }
  }
}

// put ppl onto the elevator car
void Car::embark(Floor &f2, int iter) {
  vector<Person> load;
  if (dir == UP) {
    load = f2.filter(UP); // user filter method for specific Dir
    f2.ClearUp();
  } else {
    load = f2.filter(DOWN);
    f2.ClearDown();
  }

  for (auto p4: load) {
    f2.RemovePerson(p4);
    p4.setEmbarkTime(iter);
    AddPerson(p4);
    Press(p4.dest);
    // pretty print
    cout << "Person " << p4.id << " embarking from floor ";
    cout << floor << " to car " << id << endl;
  }
}

// remove ppl from the elevator
void Car::disembark(Floor f3, int iter, vector<Person> &allPersons) {
  Reset(floor);
  for (vector<Person>::iterator i1 = persons.begin(); i1 != persons.end(); i1++) {
    if (i1->dest == floor) {
      cout << "Person " << i1->id << " disembarking from car ";
      cout << id << " to floor " << floor;
      cout << " time " << iter << endl;

      i1->setArriveTime(iter);
      allPersons.push_back(*i1);
      persons.erase(i1);
      i1--;
    }
  }
}

void Car::summary() {
  for (auto p5: persons) {
    cout << "in car " << id << ": ";
    p5.print();
  }
}