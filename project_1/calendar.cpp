// ------- Calendar -------
// This program got too bloated and it's probably a result of
// bad design on my part. At least now we know what not to do.

#include <iostream>
#include <cstdlib>
#include <fstream> // read in files
#include <string> // getline
#include <vector>
#include <sstream> // StringStream
#include <unordered_map> // hash table to store dates & desc.

using namespace std;

void printCalendar(int month, int year, unordered_map <string, string> &);
bool isLeapYear(int year);
unsigned dayOfWeek(unsigned year, unsigned month, unsigned day);
bool isSpecialDate(int month, int date, int year, unordered_map <string, string> &);
vector<string> splitByDelimiter(string &line, char c);
string trim(const string &);

// TODO:
// - [x] read in file with all configurations
// - [x] push all values into hash table
// - [ ] output all values that were printed

int main(int argc, char** argv) {
  int argCount = argc - 1;
  if (argc < 3) {
    cout << "Enter at least 2 args: " << argCount << " argument(s) given" << endl;
    return 0;
  }

  // get 3 inputs from cli
  string month_str = argv[1];
  string year_str = argv[2];
  
  // month, year validation
  if (month_str.length() > 2 || year_str.length() > 4) {
    cout << "Invalid inputs." << endl;
    return 0;
  }

  // read file with holidays (eg: "./cal 10 2019 dates.txt")
  unordered_map <string, string> specialDates;
  if (argCount == 3) {
    string filename = argv[3];
    ifstream input(filename); // read in file & output

    if (!input.is_open()) {
      cout << "ERROR: Could not load file named: \"" << filename << "\"" << endl;
      return 0;
    }

    string line;
    while (getline(input, line)) {
      // a pipe ('|') separates <date> and <description>
      vector<string> temp = splitByDelimiter(line, '|');
      string date = trim(temp[0]); // take out whitespace
      string desc = temp[1];

      specialDates[date] = desc;
    }
  }

  // convert string input to ints
  int month = stoi(month_str);
  int year = stoi(year_str);

  // print full calendar
  printCalendar(month, year, specialDates);
}

void printCalendar(int month, int year, unordered_map <string, string> &map) {
  // number valid validation
  if (month < 1 || month > 12) {
    cout << "Invalid month input" << endl;
    return;
  }
  // all 12 month strings saved
  string months[12]  = {
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
  };

  cout << "Calendar for " << months[month - 1] << " " << year << endl;

  // just in case...
  string days_of_week[7] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  string days_of_week_string = "|Sun|Mon|Tue|Wed|Thu|Fri|Sat|";

  cout << "-----------------------------" << endl;
  cout << days_of_week_string << endl;
  cout << "-----------------------------" << endl;

  // known day counts for each month
  int days[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };

  bool is_leap = isLeapYear(year);
  if (is_leap) {
    // february has 29 days on a leap year
    days[1] = 29;
  }

  // formatted string output
  int firstDay = dayOfWeek(month, 1, year);

  // usually 5 "rows"/weeks but can rarely be 4 rows (ex. Feb 2026)
  int rowsInMonth = (month == 1 && firstDay == 0 && !is_leap) ? 4 : 5;
  int daysInMonth = days[month - 1];

  // loop through start date 7 times
  int currentDate = 1;
  int hasBeen7 = 0;

  // first few blank boxes (if any)
  for (int i = 0; i < firstDay; i++) {
    cout << "|   ";
    hasBeen7++;
  }

  // What does this code even mean?? Looks like there's 2 of us.
  // I can kind of understand the output but the logic is confusing :/
  // Maybe this is a good reason to write **good** comments
  while (true) {
    if (currentDate > daysInMonth) {
      // print out the rest of the blocks
      cout << "|";
      // remaining of the ROW (if the last row is empty)
      for (int i = 0; i < (7 - hasBeen7); i++) {
        cout << "   |";
      }
      break;
    }
    if (hasBeen7 >= 7) {
      cout << "|\n" << "|";
      for (int i = 0; i < 7; i++) {
        cout << (isSpecialDate(month, currentDate - (7-i), year, map) ? " * |" : "   |");
      }
      cout << "\n-----------------------------" << endl;
      hasBeen7 = 0;
    }
    
    // print text output/cell
    string extraSpace = (currentDate >= 10) ? "" : " ";
    cout << "| " << extraSpace << currentDate;

    hasBeen7++;
    currentDate++;
  }
  // final block for dates
  cout << endl;

  // last row of dates with buffer and another asterisk location
  cout << '|';
  for (int i = 0; i < 7; i++) {
    int specialDate = daysInMonth - (hasBeen7 - i) + 1;
    cout << (isSpecialDate(month, specialDate, year, map) ? " * |" : "   |");
  }
  // empty line for aesthetic
  cout << endl;
}

// is a special day (from dates.txt file)
bool isSpecialDate(int month, int date, int year, unordered_map <string, string> &map) {
  if (month < 1 || month > 12) {
    cout << "Invalid month input" << endl;
    return false;
  }

  // dates added by default
  // July 4, October 31, December 25

  // TODO: use hash table & check if the date exists within the table
  stringstream streamDate;
  streamDate << month << "/" << date << "/" << year;
  string checkDate = streamDate.str();
  // cout << "looking for: " << checkDate << endl;

  return map.find(checkDate) != map.end();
}

bool isLeapYear(int year) {
  return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

// Algorithm:
// tondering.dk/claus/cal/chrweek.php#calcdow
// Returns: 0=Sunday, 1=Monday, etc
unsigned dayOfWeek(unsigned month, unsigned day, unsigned year) {
  unsigned a, y, m;
  a = (14 - month) / 12;
  y = year - a;
  m = month + (12 * a) - 2;
  // Gregorian:
  return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

// splits by a key (space, comma, etc.)
vector<string> splitByDelimiter(string &line, char c) {
  vector<string> lines;
  string token;
  stringstream ss(line);
  while (getline(ss, token, c)) {
    lines.push_back(token);
  }
  return lines;
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