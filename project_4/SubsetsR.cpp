#include <iostream>
#include <vector>
#include <sstream>
#include <cmath> // pow (exponential)

using namespace std;

void subsetsRecursive(vector<string> &arr_str, vector<string> &results, string prepend="", int i=0);

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

  // the meat
  vector<string> combinations;
  subsetsRecursive(cli_args, combinations);

  cout << "---------------" << endl;
  cout << "Printing combinations" << endl;
  cout << "---------------" << endl;

  for (int i = 0; i < combinations.size(); i++) {
    cout << combinations[i] << endl;
  }

}

void subsetsRecursive(vector<string> &arr_str, vector<string> &results, string prepend, int i) {
  int arrStrLen = arr_str.size();

  // if at the end of vector
  if (i == arrStrLen) {
    results.push_back(prepend);
    return;
  }

  if (prepend == "") {
    subsetsRecursive(arr_str, results, arr_str[i], i + 1);
  } else {
    // give an extra space between values
    subsetsRecursive(arr_str, results, prepend + " " + arr_str[i], i + 1);
  }
  subsetsRecursive(arr_str, results, prepend, i + 1);
}

// void subsetsRecursive(vector<string> &results, vector<string> &str_values, string prepend, int i) {
//   int str_size = str_values.size();

//   // if at last item in vector
//   if (i == str_size) {
//     // results.push_back(prepend);
//     return;
//   }

//   // concat. string with value at i
//   subsetsRecursive(results, str_values, prepend + str_values.at(i), i+1);
//   subsetsRecursive(results, str_values, prepend, i+1);
// }

// void subsetsRecursive(vector<string> &results, vector<string> &str_values, string prepend, int i) {
//   int str_size = str_values.size();

//   // if at last item in vector
//   if (i == str_size) {
//     // results.push_back(prepend);
//     cout << prepend << endl;
//     return;
//   }

//   // concat. string with value at i
//   subsetsRecursive(results, str_values, prepend + str_values.at(i), i+1);
//   subsetsRecursive(results, str_values, prepend, i+1);
// }