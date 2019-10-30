#include <iostream>
#include "Polynomial.hpp"

using namespace std;

bool handleCommand(string &);
void lowercaseString(string &);
bool stringStartsWith(string &, string);

int main() {
  // not expecting any command line input...
  cout << "+---------------------+" << endl;
  cout << "|      Polynomial     |" << endl;
  cout << "+---------------------+" << endl;

  string userInput = "";

  cout << "> ";
  while (getline(cin, userInput)) {
    // lowercase the user input
    lowercaseString(userInput);

    bool quit = handleCommand(userInput);

    if (quit) break; // if the return from the function is true
    cout << "> ";
  }

  return 0;
}

// HANDLE_COMMAND: take in user input & return false if stay in loop
// take in user input & translate to Polynomial calls
bool handleCommand(string &cmd) {
  if (cmd == "quit") {
    return true;
  }
  
  vector<string> components = splitByDelimiter(cmd, ' ');
  string command = components[0];
  int numArguments = components.size();

  // SUM (add 2 polynomials)
  if (command == "sum") {
    
    cout << "----- SUM -----" << endl;
    if (numArguments != 3) {
      cout << "Invalid input. Enter 3 inputs." << endl;
      return false;
    }
    // get next 2 items in components
    Polynomial a = Polynomial(components[1]);
    Polynomial b = Polynomial(components[2]);
    // make a & b polynomials based off it
    // if its not 2 then error
    
  } // PRODUCT (multiply out polynomials)
  else if (command == "prod") {
    cout << "--- PRODUCT ---" << endl;
    // check for invalid # of arguments
    if (numArguments != 3) {
      cout << "Invalid input. Enter 3 inputs." << endl;
      return false;
    }

  } // DERIVATIVE of polynomial
  else if (command == "deriv") {
    cout << "-  DERIVATIVE -" << endl;
    // check for invalid # of arguments
    if (numArguments != 2) {
      cout << "Invalid input. Enter 2 inputs." << endl;
      return false;
    }

  } // ROOT of polynomial
  // use N-R iteration...
  else if (command == "root") {
    cout << "---- ROOTS ----" << endl;
    // check for invalid # of arguments
    if (numArguments != 2) {
      cout << "Invalid input. Enter 2 inputs." << endl;
      return false;
    }

  } else { // ELSE reprint out the user input
    cout << cmd << endl;
  }
  return false; // don't quit (references back to loop)
} // end handleCommand

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