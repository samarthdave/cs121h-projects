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
bool Person::operator==(const Person& p) {
  return (this->id == p.id);
}

// comparison used for sorting based on start time in summary
bool Person::operator<(const Person& p) const {
  return this->start < p.start;
}

void Person::print() {
  // start: when they pressed, embark: when elevator arrived, arrive when car dropped them
  // ARRIVED - is the person still on the elevator when simulation ends?
  printf("PERSON id %d src %d dest %d start %d embarked %d arrived %d", id, src, dest, start, embarkTime, arriveTime);
  if (embarkTime == -1) {
    printf(" WAITING on FLOOR %d", src);
  }
  if (arriveTime != -1) {
    printf(" ARRIVED traveltime %d", arriveTime - start);
  }
  printf("\n");
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