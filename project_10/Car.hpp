#include <vector>

#include "Floor.hpp"
#include "Person.hpp"

using namespace std;

#ifndef _Car_Guard
#define _Car_Guard

class Car : public Container {
// private members
private:
  enum State {
    IDLE,
    MOVING,
    LOADING,
    UNLOADING,
    // OPENING,
    // CLOSING,
    // CLOSED
  }; // whatever states you want

// public members
public:
  int id; // set in constructor
  int floor;
  int capacity; // don't let more than 10 ppl on
  State state;
  Dir dir; // 0 is down, 1 is up
  int nfloors;
  // initialize with id and # of floors;
  // initilize state, dir, and buttons
  Car(int i, int f);
  string toString();
  void printSymbolic(); // print something like "CAR0[3]^"
  // this is where all the logic goes...
  void update(vector<Floor>& floors, int iter, vector<Person>& allPersons);
  // it is important to get these functions right...
  void embark(Floor& floor, int iter);
  void disembark(Floor floor, int iter, vector<Person>& allPersons);
  static bool withinRange(int floor, int move, int nfloors);
  void summary();
};

#endif // guard for Car