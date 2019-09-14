#include <iostream>
#include <cstdlib>

using namespace std;

void printCalendar(int month, int year);
bool isLeapYear(int year);
unsigned day_of_week(unsigned year, unsigned month, unsigned day);

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

  int month = stoi(month_str);
  int year = stoi(year_str);

  printCalendar(month, year);
}

void printCalendar(int month, int year) {
  // number valid validation
  if (month < 0 || month > 12) {
    cout << "Invalid month input" << endl;
    return;
  }
  string months[12]  = {
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
  };

  cout << "Calendar for " << months[month - 1] << " " << year << endl;

  // string days_of_week[7] = {
  //   "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  // };
  string dash_bar = "|---------------------------|";
  string days_of_week = "|Sun|Mon|Tue|Wed|Thu|Fri|Sat|";

  cout << dash_bar << endl;
  cout << days_of_week << endl;
  cout << dash_bar << endl;

  // get start date
  // known start values
  int days[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };

  bool is_leap = isLeapYear(year);

  if (is_leap) {
    // february has 29 days on a leap year
    days[1] = 29;
  }

  // formatted string output
  int first_day = day_of_week(month, 1, year);

  cout << "the first day is " << first_day << endl;
}

bool isLeapYear(int year) {
  return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

// Algorithm:
// tondering.dk/claus/cal/chrweek.php#calcdow
// Returns: 0=Sunday, 1=Monday, etc
unsigned day_of_week(unsigned month, unsigned day, unsigned year) {
  unsigned a, y, m;
  a = (14 - month) / 12;
  y = year - a;
  m = month + (12 * a) - 2;
  // Gregorian:
  return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}