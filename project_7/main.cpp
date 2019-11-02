#include <iostream>
#include "Polynomial.hpp"

using namespace std;

bool handleCommand(string &);
bool isInvalidInput(string &);
void lowercaseString(string &);
bool stringStartsWith(string &, string);

int main() {
  // not expecting any command line input...
  cout << "+---------------------+" << endl;
  cout << "|      Polynomial     |" << endl;
  cout << "+---------------------+" << endl;

  cout << "Options: [sum, prod, deriv, root, quit]\n" << endl;

  string userInput = "";

  do {
    cout << "> "; // to indicate user input
    // get user input & save to string
    getline(cin, userInput);
    // duh...
    lowercaseString(userInput);
    // check for invalid input (size checker)
    if (isInvalidInput(userInput)) {
      cout << "Invalid input." << endl;
      break;
    }
    // while the function doesn't return true
  } while(!handleCommand(userInput));

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
      cout << "Invalid input. Enter 2 polynomials." << endl;
      return false; // start over
    }
    // get next 2 items in components
    Polynomial a = Polynomial(components[1]);
    Polynomial b = Polynomial(components[2]);
    
    // print out
    cout << "A: " << a.toString() << endl;
    cout << "B: " << b.toString() << endl;

    cout << "A+B: " << (a+b).toString() << endl;

  }  
  // PRODUCT (multiply out polynomials)
  else if (command == "prod") {
    cout << "--- PRODUCT ---" << endl;
    // check for invalid # of arguments
    if (numArguments != 3) {
      cout << "Invalid input. Enter 2 polynomials." << endl;
      return false;
    }
    // get next 2 items in components
    Polynomial a = Polynomial(components[1]);
    Polynomial b = Polynomial(components[2]);

    // print out
    cout << "A: " << a.toString() << endl;
    cout << "B: " << b.toString() << endl;

    cout << "A*B: " << (a*b).toString() << endl;
  }
  // DERIVATIVE of polynomial
  else if (command == "deriv") {
    cout << "-  DERIVATIVE -" << endl;
    // check for invalid # of arguments
    if (numArguments != 2) {
      cout << "Invalid input. Enter 2 values." << endl;
      return false;
    }

    // pull the polynomial from array & print it
    Polynomial a = Polynomial(components[1]);
    cout << "A: " << a.toString() << endl;
    // print the derivative
    cout << a.derivative().toString() << endl;

  }
  // ROOT of polynomial
  // use N-R iteration...
  else if (command == "root") {
    cout << "---- ROOTS ----" << endl;
    // check for invalid # of arguments
    if (numArguments != 2) {
      cout << "Invalid input. Enter 2 values." << endl;
      return false;
    }

    // pull the polynomial from array & print it
    Polynomial a = Polynomial(components[1]);
    cout << "A: " << a.toString() << endl;

    // cout << a.root() << endl;

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

bool isInvalidInput(string &a) {
  int strSize = a.length();
  return strSize <= 1;
}