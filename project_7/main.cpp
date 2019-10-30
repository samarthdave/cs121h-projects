#include <iostream>
// #include "Polynomial.hpp"

using namespace std;

void lowercaseString(string &);
bool stringStartsWith(string &, string);

int main() {
  // not expecting any command line input...
  cout << "-----------------------" << endl;
  cout << "       Polynomial      " << endl;
  cout << "-----------------------" << endl;

  // Polynomial * test = new Polynomial("sdfsd");

  string userInput = "";

  while (cin >> userInput) {
    // lowercase the user input
    lowercaseString(userInput);

    if (userInput == "quit") {
      break;
    } // SUM (add 2 polynomials)
    else if (stringStartsWith(userInput, "sum")) {
      cout << "SUMMING" << endl;
    } // PRODUCT (multiply out polynomials)
    else if (stringStartsWith(userInput, "prod")) {
      cout << "PRODUCT" << endl;
    } // DERIVATIVE of polynomial
    else if (stringStartsWith(userInput, "deriv")) {
      cout << "DERIVATIVE" << endl;
    } // ROOT of polynomial
    // USER N-R iteration!
    else if (stringStartsWith(userInput, "root")) {
      cout << "ROOTS" << endl;
    } // ELSE reprint out the user input
    else {
      cout << userInput << endl;
    }
  }

  return 0;
}

// LOWERCASE a string in place
void lowercaseString(string &a) {
  for (int i = 0; i < a.length(); i++) {
    a[i] = tolower(a[i]);
  }
}

// string starts with another string?
bool stringStartsWith(string &item, string search) {
  return item.find(search) == 0;
}