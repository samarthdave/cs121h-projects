// --------------------
//    Polynomial.hpp
// --------------------
// CLASS Polynomial:

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <vector>

using namespace std;

class Polynomial {
  // PUBLIC members
  public:
    Polynomial(string);
  
  // PRIVATE members
  private:
    vector<double> values;
};

#endif // Polynomial_hpp