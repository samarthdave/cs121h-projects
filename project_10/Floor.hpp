#include <iostream>

// order matters:
// include Person before Container
#include "Person.hpp"
#include "Container.hpp"

using namespace std;

#ifndef _Floor_hpp
#define _Floor_hpp

class Floor : public Container {
// private members
  int id;
// public members
public:
  Floor(int i); // pass-in id; initialize 2 buttons to false
  bool UpPressed();
  bool DownPressed();
  void PressUp();
  void PressDown();
  void ClearUp();
  void ClearDown();
  string toString();
};

#endif // guard for Floor