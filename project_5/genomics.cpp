#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> // duh...
#include <cstdio> // printf
#include <string> // getline, stoi
#include <cstdlib> // exit function
#include <cmath> // pow, floor
#include <algorithm> // reverse (for reversing a string)

#include "codons.hpp"

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
  int geneLength;
};

struct Info {
  char homopolymerRepeatLetter;
  char homopolymerRepeatCount;
  int homopolymerLongestLoc;
};

// prototype (defining signature)
bool stringEndsWith(string &value, string &ending);
Info readGenomeFromFile(string&, string&);
vector<Gene> readProtTable(string&, Info&);
vector<string> splitByDelimiter(string&, char);
string lowercaseString(string a);
double calculateSD(vector<Gene> &, double &);
string print_seq(Gene&, string &);
void printOutAminoAcidSequence(string &);

int main(int argc, char *argv[]) {
  if (argc == 0 || argc == 1) {
      printf("Error: No value entered as argument; Need filename.\n");
      printf("Enter the FASTA file as a command line argument.\n");
      exit(1);
  } else if (argc == 2) {
    printf("Enter prot table file (optional) as second argument.\n");
  }

  string genomeFilename = argv[1];
  // save genome file output
  string allBasePairs;
  Info return_1 = readGenomeFromFile(genomeFilename, allBasePairs);
  // read in protein table (if prot table passed)
  
  if (argc >= 3) {
    string protTableFilename = argv[2];
    vector<Gene> allGenes = readProtTable(protTableFilename, return_1);

    // if looking for a gene!
    string nameOrID = "";
    if (argc == 4) { // read the name or id
      nameOrID = argv[3];
      cout << "--------------------------------------" << endl;
      cout << "Finding gene with id " << nameOrID << endl;
      
      // loop thru array of genes
      // if you find it, print seq of the start and end
      for (int i = 0; i < allGenes.size(); i++) {
        if (allGenes[i].orfID == nameOrID) {
          Gene temp = allGenes[i];
          string subStrValue = print_seq(temp, allBasePairs);
          printOutAminoAcidSequence(subStrValue);
        }
      }
    }
  }
}

// Info (a struct with data so I don't have to use global variables)
// READ in file and push to allBasePairs
Info readGenomeFromFile(string &filename, string &allBasePairs) {
  Info returnMe;
  string FASTA_EXTENSION = ".fasta";
  // read file from filename and create stream
  ifstream fileStream;
  fileStream.open(filename);

  // if error reading file
  if (!fileStream.is_open()) {
    cerr << "Could not open file: " << filename << endl;
    exit(1);
    return returnMe;
  }
  // check file type
  if (!stringEndsWith(filename, FASTA_EXTENSION)) {
    printf("Error: file extension is invalid. Expected %s. Got %s.", FASTA_EXTENSION.c_str(), filename.c_str());
    exit(1);
    return returnMe;
  }

  int lineCount = 0;
  int guanine_and_cytosine = 0;
  int allBasePairCount = 0;
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
  // for easier return value
  returnMe.homopolymerRepeatLetter = letter;
  returnMe.homopolymerRepeatCount = maxCount;
  returnMe.homopolymerLongestLoc = maxEndLocation;
  return returnMe;
}

// convert 3 letter codons to amino acid
void printOutAminoAcidSequence(string &subStrValue) {
  cout << endl;
  cout << "------------------------------" << endl;
  cout << "Printing translated set" << endl;
  int substrLength = subStrValue.length();

  int c = 1;
  printf("%8d ", c);
  for (int f = 0; f < substrLength; f += 3) {
    string s = subStrValue.substr(f, 3);
    cout << aa(s);
    if (c % 70 == 0) { printf("\n%8d ", c + 1); }
    c += 1;
  }

}

// vector<string> readProtTable(...)
// input file and push info into a vector of structs
// filename --> read me and return a vector with the important values
vector<Gene> readProtTable(string &filename, Info &return_1) {
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
  vector<int> geneLengths;
  string homoPolymerLocation = "none";
  // Gene count, min max
  int GENES_COUNT = 0;
  int GENES_LENGTH_TOTAL = 0; // for average
  int LAST_COORD_VALUE = 0;
  int GENES_MIN_SIZE; // largest size
  int GENES_MAX_SIZE; // smallest size
  // integenic region:
  int MAX_INTERGENIC = 0;
  string intergenicMaxLocation = "";
  // -------------------
  int MIN_INTERGENIC = 0;
  string intergenicMinLocation = "";
  // -------------------
  int TOTAL_INTERGENIC = 0;
  int INTERGENIC_COUNT = 0;
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
      temp[8],       // orfID (ex. "Rv2401" or "SACOL2049")
      geneLength     // difference value between s2 and s1 plus 1
    };
    
    // ------------- stats stuff -----------
    // if first run
    if (GENES_COUNT == 0) {
      GENES_MIN_SIZE = geneLength;
      GENES_MAX_SIZE = geneLength;
    } else {
      Gene prevGene = all_genes[GENES_COUNT - 1];
      // is homopolymer between?
      if (prevGene.endCoord < return_1.homopolymerLongestLoc && return_1.homopolymerLongestLoc < t.startCoord) {
        homoPolymerLocation = prevGene.orfID;
      }

      // integenic region
      int intergenicDiff = s1 - prevGene.endCoord;
      // compare values now to min and max
      if (intergenicDiff > MAX_INTERGENIC) {
        MAX_INTERGENIC = intergenicDiff + 1; // account for last bp
        intergenicMaxLocation = prevGene.orfID;
      }
      if (intergenicDiff < MIN_INTERGENIC) {
        MIN_INTERGENIC = intergenicDiff + 1; // account for last bp
        intergenicMinLocation = prevGene.orfID;
      }
      TOTAL_INTERGENIC += intergenicDiff;
      INTERGENIC_COUNT += 1;

      if (geneLength > GENES_MAX_SIZE) {
        GENES_MAX_SIZE = geneLength;
      }
      if (geneLength < GENES_MIN_SIZE) {
        GENES_MIN_SIZE = geneLength;
      }
    }
    // last coord
    if (s2 > LAST_COORD_VALUE) { LAST_COORD_VALUE = s2; }
    
    // count up by one run
    GENES_COUNT += 1;
    GENES_LENGTH_TOTAL += geneLength;
    
    // push it to the list
    all_genes.push_back(t);
  }

  // [ ] print out statistics about genes
  int GENES_SIZE = all_genes.size();

  // calculating stats:
  // double meanGeneLength
  double meanGeneSize = GENES_LENGTH_TOTAL / (double)GENES_COUNT;
  // standard dev.
  double standardDev = calculateSD(all_genes, meanGeneSize);
  // coding fraction / percentage
  double codingFraction = GENES_LENGTH_TOTAL / (double) LAST_COORD_VALUE * 100;
  // intergenic region
  double intergenicAvg = floor(TOTAL_INTERGENIC / (double)INTERGENIC_COUNT);

  // ------------------------------------------------------------
  cout << "[PROT TABLE]: num genes - " << GENES_SIZE << endl;
  cout << "------------------------------------------" << endl;
  cout << "Coding Fraction: " << codingFraction << "%" << endl;
  cout << "gene sizes: [" << GENES_MIN_SIZE << "," << GENES_MAX_SIZE << "], mean=" << meanGeneSize << " bp, stdev=" << standardDev << endl;
  cout << "intergenic mean size: " << intergenicAvg << endl;
  cout << "largest intergenic region: " << MAX_INTERGENIC << " (after " << intergenicMaxLocation << ")" << endl;
  cout << "smallest intergenic region: " << MIN_INTERGENIC << " (after " << intergenicMinLocation << ")" << endl;
  cout << "Longest homopolymer @ coord " << return_1.homopolymerLongestLoc << ") after: " << homoPolymerLocation << endl;

  // close file stream
  fileStream.close();
  return all_genes;
}

string print_seq(Gene &t, string &basePairs) {
  if (t.endCoord < t.startCoord) {
    cout << "ERROR: End is less than start. Cannot substring that." << endl;
    exit(1);
    return "";
  }

  string oldSubstr = basePairs.substr(t.startCoord - 4, t.endCoord - t.startCoord + 4);
  string mainSubstr = oldSubstr;
  // remove the first 3 letters (start)
  mainSubstr.erase(0, 3);

  if (t.strand == '-') {
    // get reverse complement
    // flip the mainSubstr and convert a, t, c, g
    reverse(mainSubstr.begin(), mainSubstr.end());
    for (int i = 0; i < mainSubstr.length(); i++) {
      switch(mainSubstr[i]) {
        case 'T': mainSubstr[i] = 'A'; break;
        case 'A': mainSubstr[i] = 'T'; break;
        case 'G': mainSubstr[i] = 'C'; break;
        case 'C': mainSubstr[i] = 'G'; break;
      }
    }
  }
  
  // print 70 letters on a row
  int BP_length = mainSubstr.length();
  int start = t.startCoord;
  int end = t.endCoord + 1;

  cout << "Printing sequence from " << start << " to " << end << " (length = " << BP_length << ")" << endl;
  cout << "------------------------------------------" << endl;

  int c = 1;
  printf("%8d ", c);
  for (int f = 0; f < mainSubstr.length(); f++) {
    cout << mainSubstr.at(f);
    if (c % 70 == 0) { printf("\n%8d ", c + 1); }
    c += 1;
  }
  return mainSubstr;
}

// bool stringEndsWith(...)
// string ends with substring?
// arg1 --> big string
// arg2 --> smaller substring
bool stringEndsWith(string &arg1, string &arg2) {
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

double calculateSD(vector<Gene> &values, double &mean) {
  int valuesSize = values.size();
  double standardDeviation = 0.0;
  for(int i = 0; i < valuesSize; i++)
    standardDeviation += pow(values[i].geneLength - mean, 2);
  return sqrt(standardDeviation / valuesSize);
}
