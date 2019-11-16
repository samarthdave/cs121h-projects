#ifndef _Person_hpp
#define _Person_hpp

enum Dir {
  DOWN = 0, UP = 1
};

class Person {
// private members
  int id;
  int start; // time when arrives at source floor
  int src; // source floor
  int dest; // destination floor
  int embarkTime; // boarding car
  int arriveTime; // arriving at destination flloor
// public members
public:
  Person(int i, int Time, int s, int d); // constuctor: pass-in id, time, src, dest
  bool operator==(const Person & p); // based on id, to check if 2 persons are same
  bool operator<(const Person & p); // based on start time, for sorting
  void setEmbarkTime(int x);
  void setArriveTime(int x);
  Dir dir(); // what direction are they travelling?
  void print();
};

#endif // guard for Person