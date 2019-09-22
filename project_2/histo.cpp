#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {

  if (argc!= 2) {
    cout << "Invalid number of inputs. Usage is \"histo FILENAME\"" << endl;
    exit(1);
  }

  string filename = argv[1];

  // read file and loop over contents to calculate mean, std-dev, etc

  return 0;

}