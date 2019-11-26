#include <iostream>
#include <sstream>
#include <iomanip> // string formatting

#include "Person.hpp"

using namespace std;

// constuctor: pass-in id, time, src, dest
Person::Person(int i, int Time, int s, int d) {
  this->id = i;
  this->start = Time;
  this->src = s;
  this->dest = d;
  // not passed in:
  this->embarkTime = -1;
  this->arriveTime = -1;
}

// are 2 objects the same (based on id?)
bool Person::operator==(const Person &p) {
  return (this->id == p.id);
}

// comparison used for sorting based on start time
// for summary!
bool Person::operator<(const Person &p) const {
  return start < p.start;
}

string Person::toString() {
  stringstream ss;

  ss << "PERSON id " << setw(3) << id << " ";
  ss << " src " << setw(3) << src; // start floor
  ss << " dest " << setw(3) << dest; // destination floor
  // when they pressed!
  ss << " start " << setw(3) << start;
  // when elevator got to person
  ss << " embarked " << setw(3) << embarkTime;
  // when elevator dropped them off
  ss << " arrived " << setw(3) << arriveTime << " ";
  // ARRIVED - is the person still on the elevator when simulation ends?
  if (embarkTime == -1) {
    ss << "WAITING on FLOOR " << src;
  } else if (arriveTime == -1) {
    ss << "ARRIVED traveltime " << (arriveTime - start);
  }
  ss << "\n";

  return ss.str();
}

Dir Person::dir() {
  return (src < dest) ? UP : DOWN;
}

void Person::print() {
  cout << (this->toString()) << endl;
}

void Person::setEmbarkTime(int x) {
  this->embarkTime = x;
}

void Person::setArriveTime(int x) {
  this->arriveTime = x;
}