#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>

using namespace std;

struct VendingItem {
  string itemName;
  int count;
  float cost;
  string toString() {
    return itemName + " costs " + count;
  }
};

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
    cout << textInput.toString() << endl;
  }
  

  // choices: "press", "exit"
  string selection = "";
  while (true) {
    cin >> selection;
    // lowercase string input
    selection = boost::algorithm::to_lower_copy(selection);
    cout << selection << endl;
    if (selection == "exit") {
      break;
    }
  }
}