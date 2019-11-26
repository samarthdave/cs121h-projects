#include <vector>
#include <algorithm> // find

#include "Container.hpp"
#include "Person.hpp"

using namespace std;

void Container::Press(int f) {
  // set selected floor to true
  buttons[f] = true;
}

bool Container::Pressed(int f) {
  // returning the current value
  return buttons[f];
}

void Container::Reset(int f) {
  // set pressed to 0 or false
  buttons[f] = false;
}

void Container::AddPerson(Person p) {
  persons.push_back(p);
}

void Container::RemovePerson(Person p) {
  persons.erase(find(persons.begin(), persons.end(), p));
}

void Container::summary() {
  for (auto p3: persons) {
    p3.print();
  }
}