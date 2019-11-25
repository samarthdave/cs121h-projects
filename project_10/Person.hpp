using namespace std;

#ifndef _Person_hpp
#define _Person_hpp

enum Dir {
  DOWN = 0, UP = 1
};

class Person {
// private members
// converted to public (for compile errors)
public:
  int id;
  int start; // time when arrives at source floor
  int src; // source floor
  int dest; // destination floor
  int embarkTime; // boarding car
  int arriveTime; // arriving at destination floor
  bool journeyComplete; // default = false
// (more) public members
  Person(int, int, int, int); // constuctor: pass-in id, time, src, dest
  bool operator==(const Person &); // based on id, to check if 2 persons are same
  bool operator<(const Person &); // based on start time, for sorting
  void setEmbarkTime(int x);
  void setArriveTime(int x);
  Dir dir(); // what direction are they travelling?
  string toString();
  void print(); // calls toString
};

#endif // guard for Person