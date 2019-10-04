// Just a file for experimenting...

// Questions I hope to answer:
// 1. How to return the least coins?
// 2. What if you're out of a certain coin?

#include <iostream>
#include <cmath> // for rounding...

using namespace std;

void dispenseChange(double &changeDue);

int main() {
  // float balance = 0.41;
  // float cost = 0.23;

  // change = 0.41 - 0.23 = 0.18
  // 0.18 is ideally: 1 dime, 1 nickel, 3 pennies
  double diff = 0.26;
  dispenseChange(diff);

  return 0;
}

// ideally, this function will also be called by the "buyItem" function
void dispenseChange(double &changeDue) {
  // check what combinations of coins that you get back (dimes, nickels, etc)
  int quarterCount = 0;
  int dimeCount = 0;
  int nickelCount = 0;

  int quartersStored = 0;
  int dimesStored = 3;
  int nickelsStored = 3;
  // assume you have all necessary coins...
  // solve float accuracy problem (fun fact: I learned this from my HS java class :))
  double changeCopy = changeDue;

  quarterCount = changeCopy / 0.25;
  changeCopy -= (quarterCount * 0.25);

  dimeCount = changeCopy / 0.1;
  changeCopy -= (dimeCount * 0.1);

  nickelCount = changeCopy / 0.05;
  changeCopy -= (nickelCount * 0.05);

  cout << "quarter " << quarterCount << endl;
  cout << "dime " << dimeCount << endl;
  cout << "nickel " << nickelCount << endl;

  // then optimize the remaining coin values (to lower into pennies, etc.)
  bool hasEnoughChange = true;

  // if not enough quarters
  if (quarterCount > quartersStored) {
    int quarterDeficiency = quarterCount - quartersStored;
    // convert quarters to dimes and nickels
    int addDimes = quarterDeficiency * 0.25 / 0.1;
    
  }

}