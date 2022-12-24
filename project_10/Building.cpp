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

// read in file & make Person instances from it
void Building::readin_traffic(string& fname) {
  // check if valid file
  fstream file;
  file.open(fname);

  if(!file.is_open()) {
    fprintf(stderr, "Error opening \"%s\".\n", fname.c_str());
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
      fprintf(stderr, "Error reading file: %s\n Error reading in line: %s\n", fname.c_str(), line.c_str());
      printf("====================");
      exit(1);
    } // error

    // person info
    Person p(id, timeIndex, src, dest);
    persons.push_back(p);
  }
}

// called from main
void Building::run() {
  int C = this->ncars;

  for (int iter = 0; iter < this->ITERS; iter++) {
    printf("\niter=%d\n", iter);
    // check for Persons whose start time is now, move to source floor
    NewArrivals(iter);

    // print out contents of floors and cars
    for (int i = 0; i < nfloors; i++) {
      int f = nfloors - i - 1;
      printf("%s", floors[f].toString().c_str());
      for (int j = 0; j < C; j++) // prints car status (ex. CAR0[3]^)
        if (cars[j].floor == f) cars[j].printSymbolic();
      printf("\n");
    }
    // print out car state (floor, count)
    for (int i = 0; i < C; i++) printf("%s\n", cars[i].toString().c_str());

    // update cars
    for (int i = 0; i < C; i++) cars[i].update(floors, iter, persons);
  } // end iters loop

  this->summary();
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

bool compare_func(const Person& p, const Person& q) {
  return p < q;
};

void Building::summary() {
  // build a lambda compare function for sorting
  sort(persons.begin(), persons.end(), compare_func);
  printf("summary\n");
  // print summary of all components
  for (auto floor : floors) {
    floor.summary();
  }
  for (auto car: cars) {
    car.summary();
  }
  for(auto person: persons) {
    person.print();
  }
}