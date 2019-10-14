#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> // duh...
#include <cstdio> // printf
#include <string> // getline, stoi

using namespace std;

struct Gene {
  string geneFunction; // A - first column
  int startCoord;      // B - 2nd col
  int endCoord;        // C - end coord
  char strand;         // D - + or -
  int proteinProductSize;    // E - in amino acids
  // f & g (don't care)
  string geneName;
  string orfID;
};

// prototype (defining signature)
inline bool stringEndsWith(string &value, string &ending);
void readGenomeFromFile(string&, string&);
vector<Gene> readProtTable(string&);
vector<string> splitByDelimiter(string&, char);
string lowercaseString(string a);

int main(int argc, char *argv[]) {
  switch (argc) {
    case 0: // don't break this, will hit case 1
    case 1:
      printf("Error: No value entered as argument; Need filename.\n");
      printf("Enter the FASTA file as a command line argument.\n");
      exit(1);
    case 2:
      printf("Enter prot table file (optional) as second argument.\n");
      break;
  }

  string genomeFilename = argv[1];
  // save genome file output
  string allBasePairs;
  readGenomeFromFile(genomeFilename, allBasePairs);
  // read in protein table (if prot table passed)
  if (argc >= 3) {
    string protTableFilename = argv[2];
    readProtTable(protTableFilename);
  }
}

// READ in file (filename) and push to allBasePairs
void readGenomeFromFile(string &filename, string &allBasePairs) {
  string FASTA_EXTENSION = ".fasta";
  // read file from filename and create stream
  ifstream fileStream;
  fileStream.open(filename);

  // if error reading file
  if (!fileStream.is_open()) {
    cerr << "Could not open file: " << filename << endl;
    exit(1);
    return;
  }
  // check file type
  if (!stringEndsWith(filename, FASTA_EXTENSION)) {
    printf("Error: file extension is invalid. Expected %s. Got %s.", FASTA_EXTENSION.c_str(), filename.c_str());
    exit(1);
    return;
  }

  int lineCount = 0;
  int allBasePairCount = 0;
  int guanine_and_cytosine = 0;
  // first line
  string headerLine = "";
  int lineLength = 0;

  string line;
  // loop through all lines and push base pairs into string
  while (getline(fileStream, line)) {
    lineCount += 1;

    // if header line
    if (lineCount == 1) {
      headerLine = line;
      cout << "------------------------------------------" << endl;
      cout << "[FASTA] Reading: " << headerLine.substr(1) << endl;
      cout << "------------------------------------------" << endl;
      continue;
    }

    // concatenate the line to the entire set
    allBasePairs += line;

    // count Gs and Cs
    lineLength = line.size();
    allBasePairCount += lineLength;

    for (int i = 0; i < lineLength; i++) {
      if (line[i] == 'G' || line[i] == 'C') {
        guanine_and_cytosine += 1;
      }
    }
  }

  // find longest homopolymer
  // using indexing in a for loop
  int currentCount = 0;
  int maxCount = 0;
  int maxEndLocation = -1;
  char letter = '-';
  char next = '-';
  // loop over all letters to find multiple occurances
  for (int i = 0; i < allBasePairCount - 1; i++) {
    // if this letter is equal to the next
    if (allBasePairs[i] == allBasePairs[i+1]) {
      currentCount += 1;
    } else {
      if (currentCount > maxCount) {
        maxCount = currentCount;
        letter = allBasePairs[i];
        maxEndLocation = i;
      }
      currentCount = 1;
    }
  }

  double gcPercent = (double) guanine_and_cytosine / allBasePairCount * 100;
  // go to the start of the letters
  int maxStartLocation = maxStartLocation - maxCount;

  // print stats from fasta file
  cout << "                fasta data                " << endl;
  cout << "length of genome: " << allBasePairCount << " bp" << endl;
  printf("GC Percent: %.3f%% (%d)\n", gcPercent, guanine_and_cytosine);
  printf("Longest homopolymer: '%c' of length %d @ coord %d\n", letter, maxCount, maxEndLocation);
  cout << "------------------------------------------" << endl;

  // close file stream
  fileStream.close();
}

// vector<string> readProtTable(...)
// input file and push info into a vector of structs
// filename --> read me and return a vector with the important values
vector<Gene> readProtTable(string &filename) {
  vector<Gene> all_genes;
  string PROT_TABLE_EXTENSION = ".prot_table";
  // read file from filename and create stream
  ifstream fileStream;
  fileStream.open(filename);

  // if error reading file
  if (!fileStream.is_open()) {
    cerr << "Could not open file: " << filename << endl;
    exit(1);
    return all_genes;
  }
  // check file type
  if (!stringEndsWith(filename, PROT_TABLE_EXTENSION)) {
    printf("Error: file extension is invalid. Expected %s. Got %s.", PROT_TABLE_EXTENSION.c_str(), filename.c_str());
    exit(1);
    return all_genes;
  }

  // stats preparation
  int GENES_COUNT = 0;
  int GENES_LENGTH_TOTAL = 0; // for average
  int GENES_MIN_SIZE; // largest size
  int GENES_MAX_SIZE; // smallest size
  // read in file
  string line;
  while (getline(fileStream, line)) {
    // file is tab separated
    vector<string> temp = splitByDelimiter(line, '\t');
    // simple checking for direciton of strand
    char strand = (temp[3] == "+") ? '+' : '-';
    int s1 = stoi(temp[1]);
    int s2 = stoi(temp[2]);
    int geneLength = s2 - s1 + 1;
    Gene t = {
      temp[0],       // geneFunction
      s1,            // startCoord
      s2,            // endCoord
      strand,        // strand - char, duh
      stoi(temp[4]), // "proteinProductSize" - protein product size 
      temp[7],       // geneName
      temp[8]        // orfID (ex. "Rv2401" or "SACOL2049")
    };
    
    // stats stuff
    if (GENES_COUNT == 0) {
      GENES_MIN_SIZE = geneLength;
      GENES_MAX_SIZE = geneLength;
    }
    GENES_COUNT += 1;
    GENES_LENGTH_TOTAL += geneLength;
    
    // push it to the list
    all_genes.push_back(t);
  }

  // [ ] print out statistics about genes
  int GENES_SIZE = all_genes.size();
  for (int i = 0; i < GENES_SIZE; i++) {

  }

  cout << "------------------------------------------" << endl;
  cout << "[PROT TABLE]: num genes - " << GENES_SIZE << endl;
  cout << "------------------------------------------" << endl;
  cout << "mean " << endl;

  // close file stream
  fileStream.close();
  return all_genes;
}

// bool stringEndsWith(...)
// string ends with substring?
// arg1 --> big string
// arg2 --> smaller substring
inline bool stringEndsWith(string &arg1, string &arg2) {
  string value = lowercaseString(arg1);
  string ending = lowercaseString(arg2);
  
  if (ending.size() > value.size())
    return false;
  return equal(ending.rbegin(), ending.rend(), value.rbegin());
}

// string lowercaseString
// a --> lowercase me!
string lowercaseString(string a) {
  for (int i = 0; i < a.length(); i++) {
    a[i] = tolower(a[i]);
  }
  return a;
}

// vector<string> splitByDelimiter
// implemented a few weeks ago
// line --> get line from stream
// c    --> (delimiter) break with this
vector<string> splitByDelimiter(string &line, char c) {
  vector<string> lines;
  string token;
  stringstream ss(line);
  while (getline(ss, token, c)) {
    lines.push_back(token);
  }
  return lines;
}