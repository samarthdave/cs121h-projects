#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// Standard deviation definition
float calculateStandardDeviation(vector<int> &items, float mean);

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "Invalid number of inputs. Usage is \"histo FILENAME\"" << endl;
    exit(1);
  }

  ifstream input;

  // argv[0] is program name
  // 1 is file name
  string filename = argv[1];
  input.open(filename);

  // read file and loop over contents to calculate mean, std-dev, etc
  int count = 0;
  int sum = 0;

  // use a boolean to ensure correct min, max values
  // instead of assuming -1
  bool firstRun = true;
  int min, max;
  vector<int> temperatures;

  int num;
  // append all the values ot the temps vector
  while (input >> num) {
    if (firstRun) {
      min = num;
      max = num;
      firstRun = false;
    }
    // comparisons for max and min
    if (num > max) {
      max = num;
    }
    if (num < min) {
      min = num;
    }
    sum += num;
    count += 1;
    temperatures.push_back(num);
  }

  float average = (float) sum / count;
  float stdDev = calculateStandardDeviation(temperatures, average);

  cout << "------------" << endl;
  cout << "count: " << count << endl;
  cout << "range: " << min << " - " << max << endl;
  cout << "mean: " << average << endl;
  cout << "std_dev: " << stdDev << endl;
  cout << "------------" << endl;

  // close the stream
  input.close();
  return 0;

}

float calculateStandardDeviation(vector<int> &items, float mean) {
  int itemCount = items.size();
  
  if (itemCount == 1) {
    cout << "ERROR: The standard deviation for 1 item does not exist. Returning -1.0" << endl;
    return -1.0;
  }

  float sumOfDifferences = 0;
  
  for (int i = 0; i < itemCount; i++) {
    sumOfDifferences += pow(float(items[i]) - mean, 2);
  }

  return sqrt((float)1/(itemCount-1) * sumOfDifferences);
}