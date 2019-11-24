#include <iostream>
#include <vector>

#include "Person.hpp"
#include "Floor.hpp"
#include "Car.hpp"

using namespace std;

#ifndef _Building_Guard
#define _Building_Guard

class Building {
// private members
private:
  int ncars;
  int nfloors;
  int ITERS;

  vector<Floor> floors;
  vector<Car> cars;
  vector<Person> persons;

// public members
public:
  Building(int numiters, int numfloors, int numcars, string fname);
  void AddPerson(Person &);
  void RemovePerson(Person &);
  void readin_traffic(string &);
  void NewArrivals(int &); // check for person whose start time has arrived
  void summary(); // print-out all persons, cars, and floors at end
  void run();
};

#endif // guard for Building