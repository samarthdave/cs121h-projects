#include <iostream>
#include <fstream>
#include <string> // stoi
#include <cstring> // strcpy
#include <iomanip> // setw
#include <utility> // pair
#include <unordered_map> // hash table
#include <vector>
#include <algorithm> // for map.find & trimming string
// for trimming:
#include <functional>
#include <cctype>
#include <locale>

using namespace std;

// prototypes
void analyzeDocument(string &);
bool simplify(string &);
int get_second( pair<string, int> i ) { return i.second; }
string lowercase(string);

// max output from cli
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

  if (argCount == 2) { // eg. "./keywords Aristotle_Ethics.txt"
    string filename = args[1];
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
  }

  // -------------------------------------------
  // insert values into a vector of pairs & sort
  // -------------------------------------------
  vector< pair<string, int> > pairs;
  for (auto it = wordHash.begin(); it != wordHash.end(); ++it) {
    pairs.push_back(make_pair(it->first, it->second));
  }

  // build a compare lambda function for sorting
  auto compare_func = [](const pair<string,int> &a, const pair<string,int> &b) {
    return a.second > b.second;
  };
  sort(pairs.begin(), pairs.end(), compare_func);

  cout << string(20, '-') << endl;
  cout << "Printing Sorted (count: " << MAX_WORDS << ")" << endl;
  cout << string(20, '-') << endl;
  int c = 0;
  for (auto pair : pairs) {
    cout << left << setw(4) << pair.second << " " << pair.first << endl;
    c++;
    if (c == MAX_WORDS) {
      break;
    }
  }

  // sort by VALUE not by key (which alternatively is easier but not what we want)
  // Approach: push all of it into a vector
  // https://stackoverflow.com/questions/2453425/how-can-i-sort-a-map-by-its-second-parameter

  // another approach
  // https://stackoverflow.com/questions/31323135/sort-an-unordered-map-using-sort

}

string lowercase(string a) {
  string s = "";
  for (char &c: a) { s += tolower(c); }
  return s;
}

// string trimming from:
// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

// trim from start
static inline string &ltrim(string &s) {
  s.erase(s.begin(), find_if(s.begin(), s.end(),
    not1(ptr_fun <int, int> (isspace))));
  return s;
}

// trim from end
static inline string &rtrim(string &s) {
  s.erase(find_if(s.rbegin(), s.rend(),
    not1(ptr_fun <int, int> (isspace))).base(), s.end());
  return s;
}

// trim from both ends
static inline string &trim(string &s) {
  return ltrim(rtrim(s));
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