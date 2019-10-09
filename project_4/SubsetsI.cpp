#include <iostream>
#include <vector>
#include <cmath> // pow (exponential)

using namespace std;

void subsetsIterative(vector<string> &, vector<vector<string>> &);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Error: Enter more than one value for the subset." << endl;
    exit(1);
  }

  vector<string> cli_args;
  for (int i = 1; i < argc; i++) {
    cli_args.push_back(argv[i]);
  }

  // subtract one bc of empty vector
  int expectedSize = pow(2, cli_args.size()) - 1;
  cout << "---------------" << endl;
  cout << "Expected length (excluding empty vector): " << expectedSize << endl;

  vector<vector<string>> combinations;

  // the meat
  subsetsIterative(cli_args, combinations);

  cout << "---------------" << endl;
  cout << "Printing combinations" << endl;
  cout << "---------------" << endl;

  for (int i = 0; i < combinations.size(); i++) {
    for (int g = 0; g < combinations[i].size(); g++) {
      cout << combinations[i][g] << ' ';
    }
    cout << endl;
  }

}

void subsetsIterative(vector<string> &cli_args, vector<vector<string>> &combinations) {
  for (int i = 0; i < cli_args.size(); i++) {
    string item = cli_args[i];

    int staticSetSize = combinations.size();
    for (int g = 0; g < staticSetSize; g++) {
      // make a copy of the set
      vector<string> tempSet = combinations[g];
      tempSet.push_back(item);
      combinations.push_back(tempSet);
    }
    vector<string> temp = { item };
    combinations.push_back(temp);
  }
  
}