#include <iostream>
#include <cstdlib>

using namespace std;

void printCalendar(int month, int year);
bool isLeapYear(int year);
unsigned dayOfWeek(unsigned year, unsigned month, unsigned day);

int main(int argc, char** argv) {
  if (argc != 3) {
    cout << "Enter 2 input values: " << (argc - 1) << " argument(s) given" << endl;
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

  // convert string input to ints
  int month = stoi(month_str);
  int year = stoi(year_str);

  // print full calendar
  printCalendar(month, year);
}

void printCalendar(int month, int year) {
  // number valid validation
  if (month < 0 || month > 12) {
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
  string dash_bar = "|---------------------------|";
  string days_of_week_string = "|Sun|Mon|Tue|Wed|Thu|Fri|Sat|";

  cout << dash_bar << endl;
  cout << days_of_week_string << endl;
  cout << dash_bar << endl;

  // get start date
  // known month values with day count in each
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
  int daysInMonth = days[month];

  // loop through start date 7 times
  int currentDate = 1;
  int hasBeen7 = 0;

  // first few blank boxes (if any)
  for (int i = 0; i < firstDay; i++) {
    cout << "|   ";
    hasBeen7++;
  }

  while (currentDate <= daysInMonth) {
    if (hasBeen7 >= 7) {
      cout << "|" << endl;
      hasBeen7 = 0;
    }
    
    // print text output/cell
    string extraSpace = (currentDate >= 10) ? "" : " ";
    cout << "| " << extraSpace << currentDate;

    hasBeen7++;
    currentDate++;
  }
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