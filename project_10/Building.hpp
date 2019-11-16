#include <iostream>
#include <vector>

#include "Floor.hpp"
#include "Car.hpp"
#include "Person.hpp"

using namespace std;

#ifndef _Building_Guard
#define _Building_Guard

class Building {
// private members
private:
  int ncars;
  int nfloors;
  int ITERS;

  vector <string> floors;
  vector <string> cars;
  vector <string> persons;

// public members
public:
  void AddPerson(Person p);
  void RemovePerson(Person p);
  void readin_traffic(char * fname);
  Building(int numiters, int numfloors, int numcars, char * fname);
  void NewArrivals(int iter); // check for person whose start time has arrived
  void summary(); // print-out all persons, cars, and floors at end
  void run() {
    for (int iter = 0; iter < ITERS; iter++) {
      cout << endl << "iter=" << iter << endl;
      // check for Persons whose start time is now, move to source floor
      NewArrivals(iter);

      // print out contents of floors and cars
      // for (int i = 0; i < nfloors; i++) {
      //   int f = nfloors - i - 1;
      //   cout << (this->floors[f]).toString();
      //   for (int j = 0; j < C; j++)
      //     if ((this->cars[j]).floor == f) (this->cars[j]).printSymbolic();
      //   cout << endl;
      // }
      // for (int i = 0; i < C; i++) cout << (this->cars[i]).toString() << endl;

      // update cars...
      // for (int i = 0; i < C; i++) (this->cars[i]).update(this->floors, iter, this->persons);
    }
  }
};

#endif // guard for Building