#include <iostream>
#include <fstream> // read file
#include <cstdio> // printf
#include <cmath> // fabs
#include <vector> // duh...

// coin constants
// #define QUARTER 0.25
// #define DIME 0.10
// #define NICKEL 0.05
// defined penny just in case I ever want to continue
#define PENNY 0.01

using namespace std;

struct VendingItem {
  string itemName;
  int count;
  double cost;
  string toString() {
    return itemName + " costs " + to_string(cost);
  }
};

bool isValidInput(string &selection);
bool isCoin(string &selection);
bool isAction(string &selection);
void drawDivider();
void printChoices(vector<VendingItem> &vendingItems);
void dispenseChange(double &balance, vector<VendingItem> &vendingItems);
void buyItem(string &item, double &balance, vector<VendingItem> &vendingItems);
char to_lowercase(char c);

int main(int argc, char* argv[]) {
  // NOTE: the "enter input" code handles each word in a sentence
  // independently and as a separate command. That's atleast how
  // cin handled it so I just went with it...

  // check if filename was given, else exit the program
  if (argc != 2) {
    cout << "Enter the filename of vending items as an argument." << endl;
    cout << "Eg. \"./vending vending1.txt\"" << endl;
    return 0;
  }

  // vector of machine items
  vector<VendingItem> vendingItems;
  // read in file
  string fileName = argv[1]; // "vending1.txt"
  ifstream infile(fileName);

  if (!infile.is_open()) {
    cout << "ERROR: Could not load you file with name: \"" << fileName << "\"" << endl;
    return 0;
  }

  string itemName;
  int count;
  double cost;

  while (infile >> itemName >> count >> cost) {
    VendingItem textInput = { itemName, count, cost };
    vendingItems.push_back(textInput);
  }

  cout << "--------- Vending Machine --------" << endl;
  // print out choices from items vector
  printChoices(vendingItems);
  
  // start off with 0 in the machine
  double balance = 0.00;
  // CONSTANTS
  double QUARTER = 0.25;
  double DIME = 0.10;
  double NICKEL = 0.05;

  // choices: "press", "quit", "change", or coins
  string selection = "";
  string prevSelection = "";
  
  while (true) {
    cout << "Options: [press|change|contents|quit|quarter|nickel|dime]" << endl;
    if (prevSelection != "") {
      cout << "(Previous choice: " << prevSelection << ")" << endl;
    }

    printf("Enter input (balance: %.2f): ", balance);
    cin >> selection;
    cout << "\nYou entered: '" << selection << "'" << endl;
    // lowercase string input
    // selection = boost::algorithm::to_lower_copy(selection);
    for (char &c: selection) {
      c = to_lowercase(c);
    }


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
        cout << "Dispensing change..." << endl;
        dispenseChange(balance, vendingItems);
      }
    }
    // if it is a coin, add its constant value
    else if (isCoinBool) {
      if (prevSelection == "press") {
        drawDivider();
        cout << "Error: You cannot dispense a coin." << endl;
        prevSelection = selection;
        continue;
      }
      if (selection == "quarter") {
        balance += QUARTER;
      } else if (selection == "dime") {
        balance += DIME;
      } else if (selection == "nickel") {
        balance += NICKEL;
      }

      // add coin to inventory
      for (int i = 0; i < vendingItems.size(); i++) {
        if (vendingItems.at(i).itemName == selection) {
          vendingItems.at(i).count += 1;
        }
      }

      printf("Your balance is %.2f.\n", balance);
    }
    else if (isFood) {
      // check prev item to see if you "pressed"
      if (prevSelection == "press") {
        // buy the item / selection
        buyItem(selection, balance, vendingItems);
        dispenseChange(balance, vendingItems);
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

// ideally, this function will also be called by the "buyItem" function
void dispenseChange(double &balance, vector<VendingItem> &vendingItems) {
  drawDivider(); // more convenient than I imagined

  // load coin values from vector
  int quarterIndex = -1;
  int dimeIndex = -1;
  int nickelIndex = -1;
  for (int i = 0; i < vendingItems.size(); i++) {
    VendingItem &temp = vendingItems.at(i);
    if (temp.itemName == "quarter") {
      quarterIndex = i;
    }
    if (temp.itemName == "dime") {
      dimeIndex = i;
    }
    if (temp.itemName == "nickel") {
      nickelIndex = i;
    }
  }

  // use indices to get references from vector array
  VendingItem &quarter = vendingItems.at(quarterIndex);
  VendingItem &dime = vendingItems.at(dimeIndex);
  VendingItem &nickel = vendingItems.at(nickelIndex);

  // check what combinations of coins that you get back (dimes, nickels, etc)
  int quartersNeeded = 0;
  int dimesNeeded = 0;
  int nickelsNeeded = 0;

  double balanceCopy = balance;
  // get smallest value of coins that we can get
  quartersNeeded = balanceCopy / 0.25;
  balanceCopy -= (quartersNeeded * 0.25);

  dimesNeeded = balanceCopy / 0.1;
  balanceCopy -= (dimesNeeded * 0.1);

  nickelsNeeded = balanceCopy / 0.05;
  balanceCopy -= (nickelsNeeded * 0.05);

  // now increment dimes, etc if not enough quarters
  double QUARTER = 0.25;
  double DIME = 0.10;
  double NICKEL = 0.05;

  while(true) {
    if ((balance - QUARTER > 0 || fabs(balance - QUARTER) < balance * 0.001)
      && quarter.count > 0) {

      balance -= QUARTER;
      cout << "change: quarter" << endl;
      quarter.count -= 1;
    } else {
      break;
    }
  }

  while(true) {
    // cout << "state: " << (balance - DIME) << ' ' << balance - DIME << ' ' << (dime.count > 0) << endl;
    if ((balance - DIME > 0 || fabs(balance - DIME) < balance * 0.001)
      && dime.count > 0) {
    // nope:
    // if (balance - DIME >= 0 && dime.count > 0) {
      balance -= DIME;
      cout << "change: dime" << endl;
      dime.count -= 1;
    } else {
      break;
    }
  }

  while(true) {
    // cout << "2nd: " << (balance - NICKEL >= 0) << ' ' << (nickel.count > 0) << endl;
    
    // turns out subtraction isn't friendly in C++
    // if (balance - NICKEL >= 0 && nickel.count > 0) {
    if ((balance - NICKEL > 0 || fabs(balance - NICKEL) < balance * 0.001)
      && nickel.count > 0) {

      balance -= NICKEL;
      cout << "change: nickel!!" << endl;
      nickel.count -= 1;
    } else {
      break;
    }
  }

}

void buyItem(string &item, double &balance, vector<VendingItem> &vendingItems) {
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
  drawDivider();
  cout << "We couldn't find the item in the machine. Did you check the contents?" << endl;
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
          selection == "nickel");
}

void drawDivider() {
  cout << "----------------------------------" << endl;
}

char to_lowercase(char c) {
	if (c >= 'A' && c <= 'Z')
		return c + 32;
	return c;
}
