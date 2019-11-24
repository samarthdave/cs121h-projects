#include <vector>
#include <algorithm>

#include "Person.hpp"

using namespace std;

bool Container::Press(int f) {
  // set selected floor to true

}

bool Pressed(int f) {
  // returning the current value
}

void Reset(int f) {
  // set pressed to 0 or false
  buttons[f] = false;
}

Container::AddPerson(Person p) {
  persons.push_back(p):
}

void RemovePerson(Person p) {
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


class Container {
public:
  // void AddPerson(Person p);
  // void RemovePerson(Person p);
};