#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> // find

#include "Building.hpp"
#include "Person.hpp"
#include "Floor.hpp"
#include "Car.hpp"

using namespace std;

Building::Building(int numiters, int numfloors, int numcars, string fname) {
  this->ncars = numcars;
  this->nfloors = numfloors;
  this->ITERS = numiters;

  // push nfloors Floor classes into this->floors
  for (int i = 0; i < numfloors; i++) {
    Floor f_temp(i);
    this->floors.push_back(f_temp);
  }

  // make the cars
  for (int i = 0; i < numcars; i++) {
    Car car_item(i, numfloors);
    this->cars.push_back(car_item);
  }

  // read in method
  this->readin_traffic(fname);
}


void Building::readin_traffic(string &fname) {
  // check if valid file
  fstream file;
  file.open(fname);

  if(!file.is_open()) {
    cerr << "Error opening \"" << fname << "\"." << endl;
    exit(1);
  }

  string line;
  int c = 0;
  while (getline(file, line)) {
    istringstream iss(line);
    c++;
    if (c == 1) { // ignore the 1st line
      continue;
    }

    string a;
    int id, timeIndex, src, dest;
    // PERSON id 1 time 24 src 1 dest 2
    if (!(iss >> a >> a >> id >> a >> timeIndex >> a >> src >> a >> dest)) {
      cerr << "Error reading file: " << fname << endl;
      cerr << "Error reading in line: " << endl;

      cout << line << "\n" << string(20, '-') << endl;
      exit(1);
    } // error

    // person info
    // cout << id << " | " << timeIndex << " | " << src << " | " << dest << endl;
    Person p(id, timeIndex, src, dest);
    persons.push_back(p);
  }
}

// called from main
void Building::run() {
  int C = this->ncars;

  for (int iter = 0; iter < this->ITERS; iter++) {
    cout << endl << "iter=" << iter << endl;
    // check for Persons whose start time is now, move to source floor
    NewArrivals(iter);

    // print out contents of floors and cars
    for (int i = 0; i < nfloors; i++) {
      int f = nfloors - i - 1;
      cout << floors[f].toString();
      for (int j = 0; j < C; j++) // prints car status (ex. CAR0[3]^)
        if (cars[j].floor == f) cars[j].printSymbolic();
      cout << endl;
    }
    // print out car state (floor, count)
    for (int i = 0; i < C; i++) cout << cars[i].toString() << endl;
    cout << string(20, '-') << endl;

    // update cars
    for (int i = 0; i < C; i++) cars[i].update(floors, iter, persons);
  } // end iters loop

  // this->summary();
}

// check for person whose start time has arrived
void Building::NewArrivals(int iter) {
  for (vector<Person>::iterator p1 = persons.begin(); p1 != persons.end(); p1++) {
    if (p1->start == iter) {
      floors[p1->src].AddPerson(*p1);
      persons.erase(p1);
      p1--;
    }
  }
}

// add/remove persons
void Building::AddPerson(Person p) {
  persons.push_back(p);
}
void Building::RemovePerson(Person p) {
  persons.erase(find(persons.begin(), persons.end(), p));
}

void Building::summary() {
  cout << string(20, '-') << endl;
  cout << "Printing summary of building" << endl;
  cout << "num cars: " << this->ncars << endl;
  cout << "floors  : " << this->nfloors << endl;
  cout << "iters   : " << this->ITERS << endl;
  cout << string(20, '-') << endl;
}