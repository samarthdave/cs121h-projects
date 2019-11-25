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
    OPENING,
    CLOSING,
    LOADING,
    UNLOADING,
    // BUSY, // just a suggestion
    CLOSED
  }; // whatever states you want
  int id; // set in constructor
  int capacity; // don't let more than this many poeple on
  State state;
  Dir dir; // 0 is down, 1 is up
  int nfloors;

// public members
public:
  int floor;
  // initialize with id and # of floors;
  // initilize state, dir, and buttons
  Car(int i, int f);
  string toString();
  void printSymbolic(); // print something like "CAR0[3]^"
  // this is where all the logic goes...
  void update(vector<Floor> &floors, int iter, vector<Person> &allPersons);
  // it is important to get these functions right...
  void embark(Floor &floor, int iter, vector<Person> &allPersons);
  void disembark(Floor &floor, int iter, vector<Person> &allPersons);
  static bool withinRange(int floor, int move, int nfloors);
};

#endif // guard for Car