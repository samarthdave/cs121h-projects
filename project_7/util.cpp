#include <sstream>
#include <vector>

#include "util.hpp"

vector<string> splitByDelimiter(string &line, char c) {
  vector<string> lines;
  string token;
  stringstream ss(line);

  while (getline(ss, token, c)) {
    lines.push_back(token);
  }

  return lines;
}