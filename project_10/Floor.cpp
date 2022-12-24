#include <sstream>

#include "Floor.hpp"

using namespace std;

Floor::Floor(int i) {
  this->id = i;

  // down & up button are false
  buttons.push_back(false);
  buttons.push_back(false);
}

vector<Person> Floor::filter(Dir dir) {
  vector<Person> ppl;
  for (auto p2: persons) {
    if (p2.dir() == dir) {
      ppl.push_back(p2);
    }
  }
  return ppl;
}

void Floor::AddPerson(Person p) {
  persons.push_back(p);
  if (p.src > p.dest) {
    PressDown();
  } else {
    PressUp();
  }
  printf("new person %d arriving on floor %d, dest=%d\n", p.id, this->id, p.dest);
}

// eg. "FLOOR 1, persons 0, up 0, down 0"
string Floor::toString() {
  stringstream ss;
  ss << "FLOOR " << id << ", ";

  // need to access parent
  int count = Container::persons.size();
  // add person count
  ss << "persons " << count << ", ";

  // up or down count?
  ss << "up " << (this->UpPressed()) << ", ";
  ss << "down " << (this->DownPressed());

  return ss.str();
}

// from run()
void Floor::summary() {
  for (auto p: persons) {
    printf("on floor %d: ", id);
    p.print();
  }
}

// is it pressed? and press
bool Floor::UpPressed() {
  return Pressed(0);
}
void Floor::PressUp() {
  Press(0);
}

// is it pressed? and press
bool Floor::DownPressed() {
  return Pressed(1);
}
void Floor::PressDown() {
  Press(1);
}

// remove press
void Floor::ClearUp() {
  Reset(0);
}
void Floor::ClearDown() {
  Reset(1);
}