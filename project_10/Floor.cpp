#include <iostream>

#include "Floor.hpp"

using namespace std;

Floor::Floor(int i) {
  cout << "hit floor constructor with " << i << endl;
}

string Floor::toString() {
  return "here is the floor to string";
}

// class Floor : public Container {
// // private members
//   int id;
// // public members
// public:
//   Floor(int i); // pass-in id; initialize 2 buttons to false
//   bool UpPressed();
//   bool DownPressed();
//   void PressUp();
//   void PressDown();
//   void ClearUp();
//   void ClearDown();
//   string toString();
// };