#include <vector>

#include "Person.hpp"

using namespace std;

#ifndef _Container_hpp
#define _Container_hpp

class Container {
// private members
protected:
  vector<bool> buttons; // true means pressed
  vector<Person> persons;

// public members
public:
  void Press(int f);
  bool Pressed(int f);
  void Reset(int f);
  void AddPerson(Person p);
  void RemovePerson(Person p);
};

#endif // guard for Container