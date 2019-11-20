#include <iostream>
#include <vector>
#include <fstream>

#include "Building.hpp"
#include "Person.hpp"

using namespace std;

Building::Building(int numiters, int numfloors, int numcars, string fname) {
  this->ncars = numcars;
  this->nfloors = numfloors;
  this->ITERS = numiters;
  // check if valid file
  fstream file;
  file.open(fname);

  if(!file.is_open()) {
    cerr << "Error opening \"" << fname << "\"." << endl;
    exit(1);
  }

}

// void Building::AddPerson(Person p);
// void Building::RemovePerson(Person p);
// void Building::readin_traffic(string fname);
// void Building::NewArrivals(int iter); // check for person whose start time has arrived
void Building::summary() {
  cout << "Printing summary of building" << endl;
  cout << this->ncars << endl;
  cout << this->nfloors << endl;
  cout << this->ITERS << endl;
  cout << string(20, '-') << endl;
}

void Building::run() {
    for (int iter = 0; iter < ITERS; iter++) {
      cout << endl << "iter=" << iter << endl;
      // check for Persons whose start time is now, move to source floor
      // NewArrivals(iter);

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