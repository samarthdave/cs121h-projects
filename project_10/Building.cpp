#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Building.hpp"
#include "Person.hpp"
#include "Floor.hpp"
#include "Car.hpp"

using namespace std;

Building::Building(int numiters, int numfloors, int numcars, string fname) {
  this->ncars = numcars;
  this->nfloors = numfloors;
  this->ITERS = numiters;

  // read in file
  this->readin_traffic(fname);
}

// void Building::AddPerson(Person p);
// void Building::RemovePerson(Person p);
// void Building::NewArrivals(int iter); // check for person whose start time has arrived

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
    
    cout << id << " | " << timeIndex << " | " << src << " | " << dest << endl;
  }
}

// 
void Building::summary() {
  cout << "Printing summary of building" << endl;
  cout << "num cars: " << this->ncars << endl;
  cout << "floors  : " << this->nfloors << endl;
  cout << "iters   : " << this->ITERS << endl;
  cout << string(20, '-') << endl;
}

// called from main
void Building::run() {
  
  for (int iter = 0; iter < ITERS; iter++) {
    int C = this->ncars;
    // cout << endl << "iter=" << iter << endl;
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

  // this -> summary();
}