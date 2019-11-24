#include <iostream>

#include "Person.hpp"

using namespace std;

// constuctor: pass-in id, time, src, dest
Person::Person(int i, int Time, int s, int d) {
  this->id = i;
  this->start = Time;
  this->src = s;
  this->dest = d;
}

// are 2 objects the same (based on id?)
bool Person::operator==(const Person &p) {
  return (this->id == p.id);
}

// comparison used for sorting based on start time
// bool operator<(const Person & p) {}

// string Person::toString() {
//   return "person toString";
// }

void Person::print() {
  cout << "this->toString()";
}