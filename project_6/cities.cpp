#include <iostream>
#include <fstream> // read file
#include <sstream> // concatenating with streams
#include <iomanip> // set precision of decimal in stream
#include <string> // stoi, to_string()
#include <cmath> // sqrt, sin, cos, atan
#include <vector>

using namespace std;

struct City {
  string name;
  double latitude;
  double longitude;
  string toString() { // could I be more Java?
    stringstream stream;
    stream << setw(15) << name << " is @ " << setw(2) << latitude << " Deg N & " << setw(2) << longitude << " Deg W";
    return stream.str();
  }
  // return distance in miles between this city and another
  // https://andrew.hedges.name/experiments/haversine/
  double distanceBetween(City s) {
    double dlon = s.longitude - longitude;
    double dlat = s.latitude - latitude;
    double a = pow(sin(dlat/2), 2) + cos(s.latitude) * cos(latitude) * pow(sin(dlon/2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = 3961 * c; // (where R is the radius of the Earth)
    return d;
  }
};

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Need at least 1 input for file name." << endl;
    exit(1);
    return 1;
  }

  string filename = argv[1];
  
  ifstream fs; // filestream (fs) only open
  fs.open(filename);

  if (!fs.is_open()) {
    cout << "File unable to be read." << endl;
    exit(1);
    return 1;
  }

  // all the cities
  vector<City> cities;
  string tempName;
  double tempLatitude, tempLongitude;
  while (fs >> tempName >> tempLatitude >> tempLongitude) {
    City t = { tempName, tempLatitude, tempLongitude };
    cities.push_back(t);
  }

  for (int i = 0; i < cities.size(); i++) {
    cout << cities[i].toString() << endl;
    if (i != 0) {
      cout << cities[i].distanceBetween(cities[i-1]) << endl;
    }
  }

  if (argc >= 3) {
    string C = "";
    int N = -1;
    
    if (argc == 3) {
      C = argv[2];
      cout << "Default value for N is 5 since none specified." << endl;
      N = 5;
    } else if (argc == 4) {
      N = stoi(argv[3]);
    }

  }
  

}