#include <iostream>
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

// comparison used for sorting based on start time in summary
bool Person::operator<(const Person &p) const {
  return this->start < p.start;
}

void Person::print() {
  cout << "PERSON id " << setw(3) << id << " ";
  cout << " src " << setw(3) << src; // start floor
  cout << " dest " << setw(3) << dest; // destination floor
  cout << " start " << setw(3) << start; // when they pressed
  cout << " embarked " << setw(3) << embarkTime; // when elevator arrived
  cout << " arrived " << setw(3) << arriveTime << " "; // when car dropped them
  // ARRIVED - is the person still on the elevator when simulation ends?
  if (embarkTime == -1) {
    cout << "WAITING on FLOOR " << src;
  }
  if (arriveTime != -1) {
    cout << "ARRIVED traveltime " << (arriveTime - start);
  }
  cout << endl;
}

Dir Person::dir() {
  return (src < dest) ? UP : DOWN;
}

void Person::setEmbarkTime(int x) {
  this->embarkTime = x;
}

void Person::setArriveTime(int x) {
  this->arriveTime = x;
}