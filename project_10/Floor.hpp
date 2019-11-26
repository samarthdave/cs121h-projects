#include <iostream>

// order matters:
// include Person before Container
#include "Person.hpp"
#include "Container.hpp"

using namespace std;

#ifndef _Floor_hpp
#define _Floor_hpp

class Floor : public Container {
// public members
public:
  int id; // converted to public member
  Floor(int i); // pass-in id; initialize 2 buttons to false
  void AddPerson(Person p);
  bool UpPressed();
  bool DownPressed();
  void PressUp();
  void PressDown();
  void ClearUp();
  void ClearDown();
  vector<Person> filter(Dir); // filter and return a copy
  string toString();
  void summary();
};

#endif // guard for Floor