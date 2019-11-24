#include <iostream>
#include <sstream>

#include "Floor.hpp"

using namespace std;

Floor::Floor(int i) {
  cout << "[FLOOR]: " << i << endl;
  this->id = i;
}

string Floor::toString() {
  stringstream ss;
  // FLOOR 1, persons 0, up 0, down 0
  // add floor #
  ss << "FLOOR " << id << ", ";

  // need to access parent
  int count = Container::persons.size();
  // add person count
  ss << "persons " << count << ", ";

  // up or down count?
  ss << "up " << UpPressed() << ", ";
  ss << "down " << DownPressed();

  return ss.str();
}

bool Floor::UpPressed() {
  return false;
}

bool Floor::DownPressed() {
  return true;
}

// class Floor : public Container {
// // private members
//   int id;
// // public members
// public:
//   void PressUp();
//   void PressDown();
//   void ClearUp();
//   void ClearDown();
//   string toString();
// };