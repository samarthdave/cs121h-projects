#include <iostream>
#include <sstream>

#include "Floor.hpp"

using namespace std;

Floor::Floor(int i) {
  cout << "[FLOOR]: " << i << endl;
  this->id = i;

  // down & up button are false
  buttons.push_back(false);
  buttons.push_back(false);
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

// accessor member
int Floor::getID() { return this->id; }

// is it pressed? and press
bool Floor::UpPressed() {
  return this->buttons[1];
}
void Floor::PressUp() {
  this->Press(1);
}

// is it pressed? and press
bool Floor::DownPressed() {
  return this->buttons[0];
}
void Floor::PressDown() {
  this->Press(0);
}

// remove press
void Floor::ClearUp() {
  this->Reset(1);
}
void Floor::ClearDown() {
  this->Reset(0);
}