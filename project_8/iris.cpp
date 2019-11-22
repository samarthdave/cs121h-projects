#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath> // sqrt
#include <stdexcept>

#include "Matrix.hpp"

using namespace std;

struct IRIS_ROW {
  float SepalLength;
  float SepalWidth;
  float PetalLength;
  float PetalWidth;
  string species;
};

// usage: "./iriscorr FILENAME SPECIES"
int main(int argv, char *argc[]) {

  cout << "-------------------------------" << endl;
  cout << "Project 8: Application 1 - Iris" << endl;
  cout << "-------------------------------" << endl;
  
  // Use Error Handling (11/22):
  string filename, selectedSpecies;
  // try {
  //   // read command line args
  //   filename = argc[1];
  //   selectedSpecies = argc[2];
  // } catch(exception &e) {
  //   cerr << "exception caught: " << e.what() << endl;
  //   throw runtime_error("Could not read filename or species");
  // }

  if (argv != 3) {
    cout << "ERROR, invalid input. Usage: \"./iriscorr FILENAME SPECIES\"" << endl;
    exit(1);
  }

  filename = argc[1];
  selectedSpecies = argc[2];
  
  // lowercase species choice
  for (char &c: selectedSpecies) { c = tolower(c); }

  cout << "Species choice: " << selectedSpecies << endl;

  // read iris setosa file
  ifstream fin;
  fin.open(filename);

  if(!fin.is_open()) {
    cout << "ERROR: Cannot open input file." << endl;
    return 1;
  }

  // the following is from iris.cpp activity in class:
  
  // make a vector for all the flower entries
  vector<IRIS_ROW> flowers;

  // variables for while loop
  int LINE_COUNT = 0;
  int SPECIES_COUNT = 0;

  string line;
  string species;

  // for calculating averages
  double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
  bool anyFlowerFound = false;

  while (getline(fin, line)) {
    LINE_COUNT += 1;

    // convert to stream so getline works
    stringstream stream(line);
    
    string data[5];
    int i = 0;
    //loop to split string
    while(getline(stream, data[i], ',')) {
      //increase repetition number
      i++;
    }

    species = data[4];
    // lowercase
    for (char &c: species) { c = tolower(c); }
    
    size_t found = species.find(selectedSpecies);

    if (found != string::npos) {
      anyFlowerFound = true; // we found an occurance!
      // if found then add to the vector
      IRIS_ROW flower;

      flower.SepalLength = stof(data[0]);
      flower.SepalWidth = stof(data[1]);
      flower.PetalLength = stof(data[2]);
      flower.PetalWidth = stof(data[3]);
      flower.species = species;
      
      // calculating average
      sum1 += flower.SepalLength;
      sum2 += flower.SepalWidth;
      sum3 += flower.PetalLength;
      sum4 += flower.PetalWidth;

      SPECIES_COUNT += 1; // should be flowers.size()
      flowers.push_back(flower);
    }

  }

  if (!anyFlowerFound) { // no flower found! might be invalid user input
    cout << "-------------------------------" << endl;
    cerr << "Error: No occurances of " << selectedSpecies << " found within the file." << endl;
    cout << "-------------------------------" << endl;
    exit(1);
  }

  // calculate average
  double sepalLengthAvg = sum1 / SPECIES_COUNT; // sepal length
  double sepalWidthAvg = sum2 / SPECIES_COUNT; // sepal width
  double petalLengthAvg = sum3 / SPECIES_COUNT; // petal length
  double petalWidthAvg = sum4 / SPECIES_COUNT; // petal width

  // push all values into Matrix
  int COLUMN_COUNT = 4;
  // make an Nx4 matrix
  Matrix irisMatrix = { SPECIES_COUNT, COLUMN_COUNT };
  
  cout << "List size: " << flowers.size() << endl;
  cout << "Species count: " << SPECIES_COUNT << endl;
  // cout << flowers[0].toString() << endl;

  for (int i = 0; i < flowers.size(); i++) {
    // center the data added to matrix:
    // subtract each value by the average of the column
    irisMatrix.set(i, 0, flowers[i].SepalLength - sepalLengthAvg);
    irisMatrix.set(i, 1, flowers[i].SepalWidth - sepalWidthAvg);
    irisMatrix.set(i, 2, flowers[i].PetalLength - petalLengthAvg);
    irisMatrix.set(i, 3, flowers[i].PetalWidth - petalWidthAvg);
  }

  cout << "-------------------------------" << endl;

  cout << "Covariance matrix: " << endl;
  Matrix covariance = irisMatrix.transpose() * irisMatrix;
  covariance.print();

  cout << "-------------------------------" << endl;

  int numRows = covariance.getNumRows();
  int numCols = covariance.getNumCols();
  // make a similar NxN matrix
  Matrix correlation = { numRows, numCols };

  // do the following operations:
  // cor(i,j) = S(i,j)/sqrt(S(i)^2*S(j)^2)
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      correlation.set(i, j, covariance.get(i,j) / sqrt(covariance.get(i,i) * covariance.get(j,j)));
    }
  }

  cout << "Correlation matrix: " << endl;
  correlation.print();

}