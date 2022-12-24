#include <string> // stoi

#include "Building.hpp"

using namespace std;

int main(int argc, char ** argv) {
  // elevator <timesteps> <floors> <car> <trafficfile>
  if (argc != 5) {
    fprintf(stderr, "Invalid input. Enter 4 options.\neg. \"./elevator <timesteps> <floors> <car> <trafficfile>\"");
    exit(1);
  }

  // read file in
  int timesteps = stoi(argv[1]);
  int floors = stoi(argv[2]);
  int cars = stoi(argv[3]);
  string filename = argv[4];

  Building b = Building(timesteps, floors, cars, filename);

  b.run();

}