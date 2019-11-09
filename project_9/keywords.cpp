#include <iostream>
#include <fstream>

using namespace std;

void analyzeDocument(string &);

int main(int argc, const char** argv) {
  cout << "------------------------" << endl;
  cout << "         Keywords       " << endl;
  cout << "------------------------" << endl;
  
  if (argc < 2 || argc > 3) {
    cerr << "Error: Invalid number of arguments provided." << endl;
    cerr << "Usage: \"./keywords FILE1\" or \"./keywords FILE1 FILE2\"" << endl;
    cerr << "where FILE1 is a document and FILE2 is a file/collection" << endl;
    exit(1);
  }

  if (argc == 2) { // eg. "./keywords Aristotle_Ethics.txt"
    string filename = argv[1];
    cout << "Reading file: " << filename << endl;
    analyzeDocument(filename);
  }

  return 0;
}

void analyzeDocument(string &filename) {
  // read in the file
  fstream file;
  file.open(filename);

  if(!file.is_open()) {
    cerr << "Cannot file file. Error opening " << filename << "." << endl;
    exit(1);
  }
  // string word;
  
  // count all the words
  // print out in a sorted order
}