#include <iostream>
#include <fstream> // read file
#include <sstream> // concatenating with streams
#include <iomanip> // setw, setprecision: formatting in streams
#include <string> // stoi, to_string()
#include <cmath> // sqrt, sin, cos, atan, fabs
#include <algorithm> // sort
#include <vector>

# define M_PI 3.14159265358979323846 /* pi */
# define EARTH_RADIUS_MI 3958.8

using namespace std;

struct City {
  string name;
  double latitude;
  double longitude;
  // use this variable for sorting when needed
  double distanceDifference;
  // am I Java yet?
  string toString() {
    // StringBuilder is to Java as stringstream is to C++
    stringstream stream;
    stream << setw(15) << name << " is @ " << setw(2) << latitude << " Deg N & " << setw(2) << longitude << " Deg W";
    return stream.str();
  }
};

double       distanceBetween(City &, City &);
vector<City> sortCities(vector<City> &, City);
void         printClosestAndFarthest(vector<City> &, City, string &, double &, string &, double &);
void         printFirstNCities(vector<City> &, City, int);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Need at least 1 input for file name." << endl;
    exit(1);
    return 1; // just in case
  }

  string filename = argv[1];
  
  ifstream fs; // filestream (fs) only open
  fs.open(filename);

  if (!fs.is_open()) {
    cout << "File unable to be read." << endl;
    exit(1);
    return 1;
  }

  // get all the cities
  vector<City> cities;
  string tempName;
  double tempLatitude, tempLongitude;
  while (fs >> tempName >> tempLatitude >> tempLongitude) {
    City t = { tempName, tempLatitude, tempLongitude };
    cities.push_back(t);
  }

  // ex: "./cities FILE" --> argc is 2
  if (argc == 2) {
    // make a copy for keeping the original list in the same imported/read order
    vector<City> citiesCopySortable;
    citiesCopySortable = cities;

    // go through the 
    string closestCities = "";
    double closestDistance = -1.0;
    // ------------------------
    string farthestCities = "";
    double farthestDistance = -1.0;
    // ------------------------
    for (int i = 0; i < cities.size(); i++) {
      City c = cities.at(i);
      vector<City> sortedCities = sortCities(citiesCopySortable, c);
      printClosestAndFarthest(sortedCities, c, closestCities, closestDistance, farthestCities, farthestDistance);
    }

    // print furthest cities
    // print closest cities
    cout << "Closest cities: " << closestCities << " @ " <<  closestDistance << " mi apart" << endl;
    cout << "Farthest cities: " << farthestCities << " @ " <<  farthestDistance << " mi apart" << endl;
  }

  if (argc >= 3) {
    string cityName = "";
    int N = -1;
    
    // CITY
    cityName = argv[2];
    // if NUMBER is (not) given
    N = (argc == 3) ? 5 : stoi(argv[3]);
    // if NUMBER is not provided
    if (argc == 3) {
      cout << "No count provided. Using N = 5 for default." << endl;
    }

    // print out first N cities that are closes to the chosen one
    vector<City> citiesCopySortable;
    citiesCopySortable = cities;

    bool cityFound = false;
    // search for the city
    for (int i = 0; i < cities.size(); i++) {
      if (cities[i].name == cityName) {
        cityFound = true;
        City c = cities.at(i);
        vector<City> sortedCities = sortCities(citiesCopySortable, c);
        // print out first N values
        printFirstNCities(sortedCities, c, N);
      }
    }

    if (!cityFound) {
      cout << "Error: \"" << cityName << "\" was not found in cities." << endl;
    }
  }

}

// return (positive) distance in miles between this city and another
// https://andrew.hedges.name/experiments/haversine/
double distanceBetween(City &c1, City &c2) {
  // convert to degrees:
  // deg * 3.141592653589793 / 180.0;
  
  double lat1 = c1.latitude * M_PI / 180.0;
  double lon1 = c1.longitude * M_PI / 180.0;
  // second set
  double lat2 = c2.latitude * M_PI / 180.0;
  double lon2 = c2.longitude * M_PI / 180.0;
  
  double dlon = fabs(lon1 - lon2);
  double dlat = fabs(lat1 - lat2);
  double a = pow(sin(dlat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2), 2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  
  return EARTH_RADIUS_MI * c;
}

// order cities from closest to furthest
bool compareCities(City a, City b) {
  return a.distanceDifference < b.distanceDifference;
}

vector<City> sortCities(vector<City> &cities, City choice) {
  int citiesSize = cities.size();
  // loop thru all cities (except choice)
  // and save all distance differences
  for (int i = 0; i < citiesSize; i++) {
    if (cities[i].name != choice.name) {
      cities[i].distanceDifference = distanceBetween(choice, cities[i]);
    } else {
      cities[i].distanceDifference = -1;
    }
  }

  // sort cities based on the distance diff property
  sort(cities.begin(), cities.end(), compareCities);

  return cities;
}

void printClosestAndFarthest(vector<City> &cities, City choice,
    // not actually global! just some names I gave them
    string &globalClosestName, double &globalShortestDistance,
    string &globalLongestName, double &globalLongestDistance) {
  
  // -------------------------------------------
  
  // initializing and config
  int citiesSize = cities.size();
  // for brevity:
  City &closest = cities[1];
  City &furthest = cities[citiesSize - 1];

  // if we're on the 1st run:
  // OR if the current shortest is shorter than global, update it
  if (globalShortestDistance == -1 || closest.distanceDifference < globalShortestDistance) {
    globalClosestName = choice.name + " and " + closest.name;
    globalShortestDistance = closest.distanceDifference;
  }

  // still first run OR
  // if the current longest is longer than global, update it
  if (globalLongestDistance == -1) {
    globalLongestName = choice.name + " and " + furthest.name;
    globalLongestDistance = furthest.distanceDifference;
  }

  // for reference (what it'll look like)
  // Alice           closest=Kingsville (20.5 mi), farthest=Dalhart (631.3 mi)
  printf("%15s", choice.name.c_str());
  printf(" - closest=%-15s (%.2f mi)", closest.name.c_str(), closest.distanceDifference);
  printf(" - furthest=%-15s (%.2f mi)\n", furthest.name.c_str(), furthest.distanceDifference);
  
}

void printFirstNCities(vector<City> &cities, City chosenCity, int n) {
  int citySize = cities.size();

  if (n >= citySize) {
    cout << "Invalid input. N cannot be larger than the city size n=" << n << " & city size=" << citySize << endl;
    return;
  }

  // all distance Differences have been calculated with "sortCities" call
  // so all left to do is print the values
  // start at 1!! (0 is the city itself w/ distance -1)
  for (int i = 1; i < n + 1; i++) {
    City &c = cities[i];
    cout << c.name << " (" << setprecision(4) << c.distanceDifference << " mi)" << endl;
  }
}