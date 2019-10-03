#include <iostream>
#include <boost/algorithm/string.hpp> // lowercase strings
#include <fstream> // read file
#include <cstdio> // printf
#include <vector> // duh...

// coin constants
#define QUARTER 0.25
#define DIME 0.10
#define NICKEL 0.05
#define PENNY 0.01

using namespace std;

struct CoinChange {
  int quarterCount;
  int dimeCount;
  int nickelCount;
  int pennyCount;
};

struct VendingItem {
  string itemName;
  int count;
  float cost;
  string toString() {
    return itemName + " costs " + to_string(cost);
  }
};

bool isValidInput(string &selection);
bool isCoin(string &selection);
bool isAction(string &selection);
void drawDivider();
void printChoices(vector<VendingItem> &vendingItems);
void dispenseChange(float &balance, vector<VendingItem> &vendingItems);
void buyItem(string &item, float &balance, vector<VendingItem> &vendingItems);

int main() {
  // vector of machine items
  vector<VendingItem> vendingItems;
  // read in file
  string fileName = "vending1.txt";
  ifstream infile(fileName);

  string itemName;
  int count;
  float cost;

  while (infile >> itemName >> count >> cost) {
    VendingItem textInput = { itemName, count, cost };
    vendingItems.push_back(textInput);
  }

  cout << "--------- Vending Machine --------" << endl;
  // print out choices from items vector
  printChoices(vendingItems);
  
  // start off with 0 in the machine
  float balance = 1.00;

  // choices: "press", "quit", "change", or coins
  string selection = "";
  string prevSelection = "";
  
  while (true) {
    cout << "Options: [press|change|contents|quit|quarter|nickel|dime|penny]" << endl;
    if (prevSelection != "") {
      cout << "(Previous choice: " << prevSelection << ")" << endl;
    }

    printf("Enter input (balance: %.2f): ", balance);
    // cout << "Enter input (balance: " << balance << "): ";
    cin >> selection;
    cout << "\nYou entered: '" << selection << "'" << endl;
    // lowercase string input
    selection = boost::algorithm::to_lower_copy(selection);

    // if it is NOT an action and NOT a coin, then it must be a food item
    bool isCoinBool = isCoin(selection);
    bool isActionBool = isAction(selection);
    bool isFood = !isCoinBool && !isActionBool;
    
    // List of verbs/actions: press, change, contents, quit
    if (isActionBool) {
      if (selection == "quit") break;
      if (selection == "contents") {
        drawDivider();
        printChoices(vendingItems);
      }
      if (selection == "change") {
        // dispense the balance of coins
        drawDivider();
        dispenseChange(balance, vendingItems);
      }
    }
    // if it is a coin, add its constant value
    else if (isCoinBool) {
      if (prevSelection == "press") {
        cout << "You cannot dispense a coin." << endl;
        prevSelection = selection;
        continue;
      }
      if (selection == "quarter") {
        balance += QUARTER;
      } else if (selection == "dime") {
        balance += DIME;
      } else if (selection == "nickel") {
        balance += NICKEL;
      } else if (selection == "penny") {
        balance += PENNY;
      }

      printf("Your balance is %.2f.\n", balance);
    }
    else if (isFood) {
      // check prev item to see if you "pressed"
      if (prevSelection == "press") {
        // buy the item / selection
        buyItem(selection, balance, vendingItems);
      } else {
        cout << "Would you like to buy " << selection << "? If so, type \"press " << selection << "\"." << endl;
      }
    }
    else {
      // press what? eg. "press" with nothing after it
      drawDivider();
      cout << "ERROR - Input not understood: " << selection << endl;
    }

    // store the last item that was inputted
    prevSelection = selection;

    // for brevity
    drawDivider();
  }

  // farewell message
  drawDivider();
  cout << "Thanks for using the vending machine!" << endl;
}

void dispenseChange(float &balance, vector<VendingItem> &vendingItems) {
  // check what combinations of coins that you get back (dimes, nickels, etc)

}

void buyItem(string &item, float &balance, vector<VendingItem> &vendingItems) {
  // check there is more than one item remaining in list...
  for (int i = 0; i < vendingItems.size(); i++) {
    VendingItem &v = vendingItems.at(i);
    // if we found the item in the list!
    if (v.itemName == item) {
      if (v.count > 0) {
        drawDivider();
        // see if you have enough money for it
        if (balance >= v.cost) {
          balance -= v.cost;
          v.count -= 1;
          cout << "Dispensing: " << item << endl;
        } else {
          cout << "You don't have enough money to buy " << item << '.' << endl;
        }
        return;
      } else {
        drawDivider();
        cout << "Look's like we're out of that item...Choose something else!" << endl;
        printChoices(vendingItems);
        return;
      }
      // since we found item, return from function
      return;
    }
  }
  cout << "We couldn't find the item in the machine. Did you check the status?" << endl;
  printChoices(vendingItems);
}

void printChoices(vector<VendingItem> &vendingItems) {
  drawDivider();
  printf("%10s|%5s|%5s\n", "Item", "Count", "Cost");
  for (int i = 0; i < vendingItems.size(); i++) {
    VendingItem v = vendingItems[i];
    printf("%10s|%5d|%5.2f\n", v.itemName.c_str(), v.count, v.cost);
  }
  drawDivider();
}

bool isValidInput(string &selection) {
  // ideally, reading from "currency.txt" file to accept
  // only those values as valid user input but this will do
  if (isCoin(selection)) {
    return true;
  }

  // actions/verbs
  if (isAction(selection)) {
    return true;
  }

  // did not pass checks
  return false;
}

bool isAction(string &selection) {
  return (selection == "contents" || selection == "quit" ||
          selection == "press" || selection == "change");
}

// I extracted this because I wanted to check if users "press" a action
// eg. "press quarter" is invalid
bool isCoin(string &selection) {
  return (selection == "quarter" || selection == "dime" ||
          selection == "nickel" || selection == "penny");
}

void drawDivider() {
  cout << "----------------------------------" << endl;
}