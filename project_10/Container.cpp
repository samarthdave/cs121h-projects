#include <vector>
#include <algorithm>

#include "Container.hpp"
#include "Person.hpp"

using namespace std;

void Container::Press(int f) {
  // set selected floor to true
  this->buttons[f] = true;
}

bool Container::Pressed(int f) {
  // returning the current value
  return this->buttons[f];
}

void Container::Reset(int f) {
  // set pressed to 0 or false
  buttons[f] = false;
}

void Container::AddPerson(Person p) {
  this->persons.push_back(p);
}

void Container::RemovePerson(Person p) {
  // search thru vector
  // int foundLoc = -1;
  // for (int i = 0; i < persons.size(); i++) {
  //   if (person[i] == this) {
  //     foundLoc = i;
  //   }
  // }

  // if (foundLoc != -1) {
  //   // remove it
  //   persons.erase();
  // }

  vector<Person>::iterator position = find(persons.begin(), persons.end(), p);
  if (position != persons.end()) // == persons.end() means the element was not found
    persons.erase(position);

  // vector<Person>::iterator it;
  // it = find (myvector.begin(), myvector.end(), p);
  // if (it != myvector.end())
  //   std::cout << "Element found in myvector: " << *it << '\n';
  // else
  //   std::cout << "Element not found in myvector\n";

  // find index, & remove it
}