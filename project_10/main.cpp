#include <iostream>
#include <string> // stoi

#include "Building.hpp"

using namespace std;

int main(int argc, char ** argv) {
  // elevator <timesteps> <floors> <car> <trafficfile>
  if (false) { // argc != 5) {
    cerr << "Invalid input. Enter 4 options." << endl;
    cerr << "eg. \"./elevator <timesteps> <floors> <car> <trafficfile>\"" << endl;
    exit(1);
  }

  // read file in
  // int timesteps = stoi(argv[1]);
  // int floors = stoi(argv[2]);
  // int cars = stoi(argv[3]);
  // string filename = argv[4];
  int timesteps = 100;
  int floors = 5;
  int cars = 1;
  string filename = "tests/traffic_5_100_0.2.txt";

  Building b = Building(timesteps, floors, cars, filename);

  b.run();

}