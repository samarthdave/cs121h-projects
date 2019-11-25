#include <iostream>
#include <sstream>
#include <iomanip> // string formatting

#include "Person.hpp"

using namespace std;

// [ ] constructor
// [x] equality operator
// [ ] comparison operator
// [x] void setEmbarkTime(int x);
// [x] void setArriveTime(int x);
// [ ] Dir dir(); // what direction are they travelling?
// string toString();
// void print(); // calls toString

// constuctor: pass-in id, time, src, dest
Person::Person(int i, int Time, int s, int d) {
  this->id = i;
  this->start = Time;
  this->src = s;
  this->dest = d;
  // not passed in:
  this->embarkTime = -1;
  this->arriveTime = -1;
  this->journeyComplete = false;
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
  // when they pressed!
  ss << " start " << setw(3) << start;
  // when elevator got to person
  ss << " embarked " << setw(3) << embarkTime;
  // when elevator dropped them off
  ss << " arrived " << setw(3) << arriveTime;
  // ARRIVED - is the person still on the elevator when simulation ends?
  if (!journeyComplete) {
    // waiting in elevator or in a car
    if (this->embarkTime != -1) // journey started
      ss << " still on car";
  } else { // if successful travel from src --> dest
    ss << " travelTime " << setw(3) << (arriveTime - start);
  }

  return ss.str();
}

void Person::print() {
  cout << (this->toString()) << endl;
}

void Person::setEmbarkTime(int x) {
  this->embarkTime = x;
}

void Person::setArriveTime(int x) {
  this->journeyComplete = true;
  this->arriveTime = x;
}