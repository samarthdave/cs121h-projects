#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Standard deviation definition
double calculateStandardDeviation(vector<double> &items, double mean);
// fucntion to print entire set
void printHistogram(vector<double> &items, double min, double max);

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
  double sum = 0;

  // use a boolean to ensure correct min, max values
  // instead of assuming -1
  bool firstRun = true;
  double min, max;
  vector<double> temperatures;

  double num;
  // append all the values to the temps vector
  while (input >> num) {
    // initialize values of min, max if it is first run
    if (firstRun) {
      min = num;
      max = num;
      // then change to false
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

  double average = (double) sum / count;
  double stdDev = calculateStandardDeviation(temperatures, average);

  cout << "------------" << endl;
  cout << "count: " << count << endl;
  cout << "range: " << min << " - " << max << endl;
  cout << "mean: " << average << endl;
  cout << "std_dev (sample): " << stdDev << endl;
  cout << "------------" << endl;

  // close the stream
  input.close();

  printHistogram(temperatures, min, max);

  return 0;

}

double calculateStandardDeviation(vector<double> &items, double mean) {
  int itemCount = items.size();
  
  if (itemCount == 1) {
    cout << "ERROR: The standard deviation for 1 item does not exist. Returning -1.0" << endl;
    return -1.0;
  }

  double sumOfDifferences = 0;
  
  for (int i = 0; i < itemCount; i++) {
    // cout << double(items[i]) << " minus " << mean << " equals " << ((double) items[i]) - mean << endl;
    sumOfDifferences += pow(double(items[i]) - mean, 2);
  }
  return sqrt(1/((double)itemCount-1) * sumOfDifferences);
}

void printHistogram(vector<double> &items, double min, double max) {
  int binCount = 20;
  int binItems[20] = { 0 }; // all values set to 0
  
  // an array for start and end of each bin
  double breakPoints[21] = { 0 };
  double jumpSize = ((double)max - min) / binCount;
  
  // set the break point values eg. 70, 70.2, 70.4, ...
  // of size binCount + 1
  for (int i = 0; i < binCount + 1; i++) {
    breakPoints[i] = min + i * jumpSize;
  }

  cout << "------------------" << endl;
  cout << "    Histogram     " << endl;
  cout << "------------------" << endl;

  // assuming that the right hand side is NOT included in the limit
  int itemsSize = items.size();
  for (int i = 0; i < itemsSize; i++) {
    double diff = items[i] - min;
    int solveForMax = diff / jumpSize;
    if (solveForMax == 0) {
      binItems[solveForMax] += 1;
    } else if (solveForMax == binCount) {
      binItems[19] += 1;
    } else {
      binItems[solveForMax] += 1;
    }
  }

  // print histogram with 'x' for values...
  for (int i = 0; i < 20; i++) {
    cout << setw(6) << breakPoints[i] << " - " << setw(6) << breakPoints[i+1] << ":" << '\0';
    cout << string(binItems[i], '*') << endl;
  }
  cout << "------------------" << endl;

}

// void printArr(double arr[], int size);
// void printArr(double arr[], int size) {
//   cout << "------------------" << endl;
//   for (int i = 0; i < size; i++) {
//     cout << arr[i] << ' ';
//   }
//   cout << "\n------------------" << endl;
// }