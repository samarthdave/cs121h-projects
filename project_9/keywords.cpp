#include <iostream>
#include <fstream>
#include <string> // stoi, trimming
#include <cstring> // strcpy
#include <iomanip> // setw
#include <utility> // pair
#include <unordered_map> // hash table
#include <vector>
#include <algorithm> // for map.find & trimming string

using namespace std;

// ----------
// prototypes
// ----------
bool simplify(string &);
int get_second( pair<string, int> i ) { return i.second; }
// read, analyze text files
void printSimple(vector< pair<string,int> > &);
void sortVector(vector< pair<string, int> > &);
void extractTable(vector< pair<string, int> > &, vector< pair<string, int> > &, int, int);
unordered_map<string, int> extractHashFromDoc(string &, int &);
vector< pair<string, int> > buildVector(unordered_map<string, int> &);

// string manipulation
string trim(const string &);
string lowercase(string);

// global: max output from cli, change using --max flag
int MAX_WORDS = 20;

int main(int argc, const char** argv) {
  cout << "------------------------" << endl;
  cout << "         Keywords       " << endl;
  cout << "------------------------" << endl;

  vector<string> args;
  // get arguments and parse for flags
  for (int i = 0; i < argc; i++) {
    // show command line args
    printf("Argument i=%d : %s\n", i, argv[i]);

    // check if it's a flag and get next item
    if (lowercase(argv[i]) == "--max" && (i+1) < argc) {
      MAX_WORDS = stoi(argv[i+1]);
      i += 1;
      continue;
    }
    
    // if not a flag, push
    args.push_back(argv[i]);
  }
  
  int argCount = args.size();
  if (argCount < 2 || argCount > 3) {
    cerr << "Error: Invalid number of arguments provided." << endl;
    cerr << "Usage: \"./keywords FILE1\" or \"./keywords FILE1 FILE2\"" << endl;
    cerr << "where FILE1 is a document and FILE2 is a file/collection" << endl;
    cout << "------------------------" << endl;
    exit(1);
  }

  unordered_map<string, int> fileMap;
  vector< pair<string, int> > vec1;
  int total1 = 0; // total word count values
  int total2 = 0; // will be passed by ref.
  string filename1 = "";

  if (argCount >= 2) {
    filename1 = args[1];
    cout << "Reading file: " << filename1 << endl;
    fileMap = extractHashFromDoc(filename1, total1);
    // unsorted vector of items
    vec1 = buildVector(fileMap);
    // pass by ref.
    sortVector(vec1);
  }

  if (argCount == 2) { // eg. "./keywords Aristotle_Ethics.txt"
    // print
    printSimple(vec1);
  }

  if (argCount == 3) { // "./keywords Aristotle_work.txt Aristotle_Collection.txt"
    // read second file/collection
    string filename2 = args[2];
    cout << "Reading second file: " << filename2 << endl;
    
    unordered_map<string, int> collectionMap = extractHashFromDoc(filename2, total2);
    // sort
    vector< pair<string, int> > vec2 = buildVector(collectionMap);
    sortVector(vec2);

    // build & print large table
    extractTable(vec1, vec2, total1, total2);
  }

  return 0;
}

struct Row {
  string word;
  int numDoc;
  double freqDoc;
  int numAll;
  double freqAll;
  double expected;
  float ratio;
};

// 2 arguments for files
void extractTable(vector< pair<string, int> > &collection,
                  vector< pair<string, int> > &document,
                  int collectionWordCount, int documentWordCount) {
  // fill vector with values, then sort based on enrichment
  vector<Row> tableItems;

  const int PC = 5; // pseudo count
  // nested loop where outer is the collection inclusive of document (inner)
  for (auto pair : collection) {
    Row r;
    r.word = pair.first;
    // forgive the nested loop... using it for a linear search through
    // is it O(n^2)? who knows...
    for (auto p2 : document) {
      if (p2.first == pair.first) {
        r.numDoc = p2.second;
        r.freqDoc = p2.second / (double)documentWordCount;
      }
    }
    double collectionFrequency = pair.second / (double)collectionWordCount;
    r.numAll = pair.second;
    r.freqAll = collectionFrequency;
    // expect(W,D) = N(D) * freq(W,C)
    double expect = documentWordCount * collectionFrequency;
    r.expected = expect;

    // enrich(W,D) = N(W,D) / expect(W,D)
    float enrich = (r.numDoc+PC) / (expect+PC);
    r.ratio = enrich;
    tableItems.push_back(r);
  }

  // sort by enrichment
  auto compare_rows = [](const Row &a, const Row &b) {
    return a.ratio > b.ratio;
  };
  sort(tableItems.begin(), tableItems.end(), compare_rows);

  // print in order
  cout << string(24, '-') << endl;
  printf("     %-10s %8s %9s %8s %10s %9s %6s\n",
        "WORD", "num(doc)", "freq(doc)", "num(all)", "freq(all)", "expected", "ratio");
  int c = 0;
  for (auto row : tableItems) {
    printf("%-15s", row.word.c_str()); // word
    printf("%-8d %6.6f", row.numDoc, row.freqDoc);
    printf("%8d %13.7f", row.numAll, row.freqAll);
    printf("%9.2f", row.expected);
    printf("%7.3f\n", row.ratio);
    c++;
    if (c >= MAX_WORDS) {
      cout << "Printed " << MAX_WORDS << " items. Use \"--max\" flag for more." << endl;
      break;
    }
  }
}

// -----------------------------------
// map<...> extractHashFromDoc(string fname)
// ----- takes in file, inserts word occurence into map
// -----------------------------------
unordered_map <string, int> extractHashFromDoc(string &filename, int &count) {
  // read in the file
  fstream file;
  file.open(filename);

  if(!file.is_open()) {
    cerr << "Error opening \"" << filename << "\"." << endl;
    exit(1);
  }
  
  // watch variables
  string word;
  int wordCount = 0;
  // use a hash
  unordered_map <string, int> wordHash;

  // loop through words in file
  while (file >> word) {
    bool keep = simplify(word); // cleanup
    
    // if year, punctuation, etc.
    if (!keep) continue;

    wordCount += 1;
    // if the word doesn't exist, then add it
    if (wordHash.find(word) == wordHash.end()) {
      wordHash[word] = 1;
    } else {
      // add to the count
      wordHash[word] += 1;
    }
    // this could simply be replaced with
    // wordHash[word] += 1;
    // since all values for int are set to 0 by default
  } // end while loop

  count = wordCount; // update count (passed by ref)
  cout << "Total words=" << wordCount << endl;

  return wordHash;
}

vector< pair<string, int> > buildVector(unordered_map<string, int> &map) {
  // ------------------------------------
  // insert values into a vector of pairs
  // ------------------------------------
  vector< pair<string, int> > pairs;
  for (auto it = map.begin(); it != map.end(); it++) {
    pairs.push_back(make_pair(it->first, it->second));
  }

  return pairs;
}

void sortVector(vector< pair<string, int> > &pairs) {
  // build a lambda compare function for sorting
  auto compare_func = [](const pair<string,int> &a, const pair<string,int> &b) {
    return a.second > b.second;
  };
  sort(pairs.begin(), pairs.end(), compare_func);
}

// print vector
void printSimple(vector< pair<string,int> > &pairs) {
  int wordsSize = pairs.size();
  cout << "--------------------" << endl;
  cout << "Printing Sorted (total=" << wordsSize << ", N=" << MAX_WORDS << ")" << endl;
  cout << "--------------------" << endl;
  int c = 0;
  
  for (auto pair : pairs) {
    cout << setw(4) << pair.second << " " << pair.first << endl;
    c++;
    if (c >= MAX_WORDS) {
      cout << "Printed " << MAX_WORDS << " items. Use \"--max\" flag for more." << endl;
      break;
    }
  }
}

string lowercase(string a) {
  string s = "";
  for (char &c: a) { s += tolower(c); }
  return s;
}

// string trimming from:
// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/

const string WHITESPACE = " \n\r\t\f\v";
string ltrim(const string &s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

// trim from both ends
string trim(const string &s) {
  return rtrim(ltrim(s));
}

bool simplify(string &text) {
  // [x] lowercase
  for (char &c: text) { c = tolower(c); }
  
  // [x] remove punctuation
  for (int i = 0, len = text.length(); i < len; i++) {
    // remove all punctuation expect hyphens
    if (ispunct(text[i]) && text[i] != '-') {
      text.erase(i--, 1);
      len = text.size();
    }
  }

  // [x] remove numbers
  // https://stackoverflow.com/questions/7352099/stdstring-to-char
  char * p;
  // char *cstr = &text[0];
  char *cstr = new char[text.length() + 1];
  strcpy(cstr, text.c_str());

  long converted = strtol(cstr, &p, 10);
  // https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
  if (*p) { /* input was not a number */ } else {
    delete [] cstr; // delete the string
    return false; // converted to a number, not allowed
  }

  // [x] remove white space
  trim(text);
  delete [] cstr; // delete the string

  return true;
}