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
  // car direction
  char token = '*';
  if (state == MOVING) {
    token = dir == UP ? '^' : 'v';
  }
  // ex: "CAR1[0]v" or "CAR3[10]^"
  printf(" CAR%d[%d]%c", this->id, (int) this->persons.size(), token);
}

void Car::update(vector<Floor>& f4, int iter, vector<Person>& allPersons) {
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
  // set direction for push size
  int moveDirection = dir == UP ? 1 : -1;
  
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
void Car::embark(Floor& f2, int iter) {
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
    printf("Person %d embarking from floor %d to car %d\n", p4.id, floor, id);
  }
}

// remove ppl from the elevator
void Car::disembark(Floor f3, int iter, vector<Person>& allPersons) {
  Reset(floor);
  for (vector<Person>::iterator i1 = persons.begin(); i1 != persons.end(); i1++) {
    if (i1->dest == floor) {
      printf("Person %d disembarking from car %d to floor %d time %d\n", i1->id, id, floor, iter);

      i1->setArriveTime(iter);
      allPersons.push_back(*i1);
      persons.erase(i1);
      i1--;
    }
  }
}

void Car::summary() {
  for (auto p5: persons) {
    printf("in car %d: ", this->id);
    p5.print();
  }
}