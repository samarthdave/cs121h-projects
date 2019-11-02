// --------------------
//    Polynomial.hpp
// --------------------

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <vector>

using namespace std;

vector<string> splitByDelimiter(string &, char);

// STRUCT Monomial
struct Monomial {
  double coefficient;
  int power;
};

// CLASS Polynomial:
class Polynomial {
// PUBLIC members
public:
  // internal use constructor
  Polynomial(vector<Monomial> &);
  // constructor
  Polynomial(string);
  // add 2 polynomials:
  Polynomial operator+(Polynomial &);

  // multiply 2 polynomials:
  Polynomial operator*(Polynomial &);

  // toString for formatted output
  string toString();

// PRIVATE members
  vector<Monomial> terms;
};

#endif // Polynomial_hpp