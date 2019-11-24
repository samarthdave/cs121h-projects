#include <iostream>
#include <sstream>
#include <iomanip> // string formatting

#include "Person.hpp"

using namespace std;

// [ ] constructor
// [x] equality operator
// [ ] comparison operator
// [ ] setEmbarkTime(int x);
// [ ] void setArriveTime(int x);
// [ ] Dir dir(); // what direction are they travelling?
// string toString();
// void print(); // calls toString

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
// for summary!
// bool operator<(const Person & p) {}

string Person::toString() {
  stringstream ss;

  ss << "PERSON: " << setw(3) << id << " ";
  ss << " src " << setw(3) << src; // start floor
  ss << " dest " << setw(3) << dest; // destination floor
  ss << " start " << setw(3) << start;
  ss << " embarked " << setw(3) << embarkTime;
  ss << " arrived " << setw(3) << arriveTime;
  // ARRIVED - is the person still on the elevator when simulation ends?
  // if person still on elevator then print
    // then print arrived -1
  ss << " PLACEHOLDER ";

  ss << " travelTime " << setw(3) << (arriveTime - start);

  return ss.str();
}

void Person::print() {
  cout << (this->toString()) << endl;
}