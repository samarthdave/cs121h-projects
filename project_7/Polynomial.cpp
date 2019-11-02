#include <iostream>
#include <vector> // duh
#include <sstream> // stringstream for toString
#include <iomanip> // std::setprecision
#include <string> // stod, stoi, etc.
#include <cmath> // sqrt, fabs

#include "Polynomial.hpp"
#include "util.hpp"

using namespace std;

// N-R stuff:
bool accurateEnough(double, double, double);
double evalPolynomialAt(Polynomial, double);

// first a constructor for if a vector of monomials is known:
Polynomial::Polynomial(vector<Monomial> &copyValues) {
  for (int i = 0; i < copyValues.size(); i++) {
    Monomial copy = copyValues[i];
    terms.push_back(copy);
  }
}

// constructor: takes in string and parses it
Polynomial::Polynomial(string input) {
  int strSize = input.size();

  int monomialCount = 1;
  for (int i = 1; i < strSize; ++i)
    if (input[i] == '+' || input[i] == '-')
      monomialCount++;

  // add '+' signs before all terms if non exists
  if (isdigit(input[0])) input.insert(0, "+");
  if (input[0] == 'x') input.insert(0, "+");
  input.append("+");
  strSize = input.size();

  int j = 0;
  // add components into list
  vector<string> monomials;
  for (int i = 1; i < strSize; ++i) {
		if (input[i] == '+' || input[i] == '-') {
      monomials.push_back(input.substr(j, i - j));
      j = i;
    }
	}

  // format all components to Cx^E
  for (int i = 0; i < monomialCount; ++i) {
    // x is the next item after the plus minus sign
    if (monomials[i][1] == 'x') {
      // 1*x^E
      monomials[i].insert(1, "1");
    }
    
    // determine if constant term or x exists
    bool xIsPresent = false;

    int len = monomials[i].size();
    for (int j = 1; j < len; ++j) {
      if (monomials[i][j] == 'x') {
        xIsPresent = true;
        if (j == len - 1) // raise to 1 power (6x is implicit 1st power)
          monomials[i].append("^1");
        break;
      }
    }
    if (!xIsPresent) // if no x exists
      monomials[i].append("x^0"); // then add x^0
  }

  //	Extracting the coefficients and exponents as numbers
  vector<int> exponents;
  vector<double> coefficients;
  // lo
  for (int i = 0; i < monomialCount; i++) {
    int monomialsSize = monomials[i].size();
    for (int g = 0; g < monomialsSize; g++) {
      if (monomials[i][g] == '^') {
        double coefficient = stod(monomials[i].substr(0, g));
        int exponent = stoi(monomials[i].substr(g + 1, monomialsSize - g));
        // push a generated value into the list
        terms.push_back(Monomial{ coefficient, exponent });
        break;
      }
    }
  }

}

// ------------------
//      MULTIPLY
// ------------------
// override c++ multiply operator for A*B

Polynomial Polynomial::operator*(Polynomial &poly2) {
  // b/c foiling in c++ seems like a pain
  // https://www.geeksforgeeks.org/multiply-two-polynomials-2/
  int m = terms.size();
  int n = poly2.terms.size();
  int totalSize = m + n - 1; // came up enough that I just saved it

  double * prod = new double[totalSize];

  for (int i = 0; i < totalSize; i++)
    prod[i] = 0.0;

  // multiply each item term by term (so basically FOIL)
  for (int i = m - 1; i >= 0; i--) {
    for (int j = n - 1; j >= 0; j--)
      prod[i + j] += terms[i].coefficient * poly2.terms[j].coefficient;
  }

  vector<Monomial> newTerms;
  // loop thru array & push into new terms
  for (int i = 0; i < totalSize; i++)
    newTerms.push_back(Monomial{ prod[i], totalSize-i-1 });

  // use the constructor to return the prod
  return Polynomial(newTerms);
}

// ------------------
//         ADD
// ------------------
// override c++ addition operator for A+B

Polynomial Polynomial::operator+(Polynomial &poly2) {
  vector<Monomial> newTerms;

  for (int i = 0; i < terms.size(); i++) {
    bool foundInRow = false;
    for (int g = 0; g < poly2.terms.size(); g++) {
      // if the exponents are equal, sum them
      if (terms[i].power == poly2.terms[g].power) {
        double coefficientSum = terms[i].coefficient + poly2.terms[g].coefficient;
        if (coefficientSum != 0.0) { // if they don't cancel out
          // keep the same exponent but add the decimal coefficients
          Monomial m1 = { coefficientSum, terms[i].power };
          // add it to the array
          newTerms.push_back(m1);
        }
        foundInRow = true; // and show we found it in 2nd array
      }
    }
    // if no match to current exponent, add it to the list
    if (!foundInRow) {
      Monomial m1 = { terms[i].coefficient, terms[i].power };
      newTerms.push_back(m1);
    }
  }

  // construct a new polynomial from the current terms
  return Polynomial(newTerms);
}

// ------------------
//       DERIVE
// ------------------
// override c++ addition operator for A+B

Polynomial Polynomial::derivative() {
  // you know the drill by now
  vector<Monomial> newTerms;

  // for (int i = terms.size() - 1; i >= 0; i--) {
  for (int i = 0; i < terms.size(); i++) {
    int exp = terms[i].power;
    double c = terms[i].coefficient;
    if (exp - 1 == -1) {
      // do nothing for derive x^0
    } else {
      Monomial t = { exp * c, exp - 1 };
      newTerms.push_back(t);
    }
    
  }

  // same design as prev. functions, create a new poly based off the terms
  return Polynomial(newTerms);
}

// ------------------
//     printRoots
// ------------------
// get the derivative, use that for evaluation

void Polynomial::printRoots(Polynomial &b) {
  vector<Monomial> c = b.terms;

  double guess = 10;
  double lastGuess;
  // just in case
  int overflowFallback = 1;
  double tangentValue = 0.0;
  // its reasonable to assume that the value should converge in 100 runs
  while (overflowFallback <= 100) {
    lastGuess = guess;
    // get intersection of the tangent with the x axis (when y = 0)
    tangentValue = evalPolynomialAt(b, guess);
    
    // if the tangent is 0, we won't divide by 0!
    if (tangentValue == 0) {
      guess = 0;
      break;
    }
    // else make a guess
    guess = (-1 * evalPolynomialAt(*this, guess)/tangentValue) + guess;
    
    // if accurate enough
    if (accurateEnough(lastGuess, guess, 0.0000001)) {
      break;
    }
    overflowFallback += 1;
  }

  // now guess (double) is the estimate of the zero
  // of the polynomial (this) since the usage is a.printRoots(Poly deriv)
  cout << "Root location: " << guess << endl;
  cout << "Value @ " << setprecision(4) << guess << " is " << setprecision(8) << evalPolynomialAt(*this, guess) << endl;
}

// ------------------
//      toString
// ------------------
// use string stream to print out a formatted polynomial

string Polynomial::toString() {
  // loop through vector of items & append to string stream
  stringstream ss;
  Monomial t; // for use in the loop

  int termsCount = terms.size();
  for (int i = 0; i < termsCount; i++) {
    Monomial t = terms[i];
    if (t.coefficient == 0.0) {
      continue;
    }
    ss << setprecision(3) << t.coefficient;
    
    if (t.power == 1) {
      ss << "x";
    }
    if (t.power > 1) { // if x^2, etc. (not x^1)
      ss << "x^" << t.power;
    }

    // if next item exists
    if (i+1 < termsCount) {
      // if next term's coeffiicent is < 0, then add space, else add plus sign
      if (terms[i+1].coefficient < 0) {
        ss << " ";
      } else if (terms[i+1].coefficient > 0) {
        ss << " + ";
      }
      // no need but for semantics only
      // else { // equal to 0!
      //   ss << "";
      // }
    }
  }
  return ss.str();
}

double evalPolynomialAt(Polynomial s, double loc) {
  double total = 0;
  
  for (int i = 0; i < s.terms.size(); i++) {
    double c = s.terms[i].coefficient;
    double e = (double)s.terms[i].power; // cast just to be safe
    total += (c*pow(loc, e));
  }

  return total;
}

// check if value squared 
bool accurateEnough(double v1, double v2, double percentAccuracy) {
  double decimal = percentAccuracy / 100;
  // is the abs difference between v1 & v2 enough?
  return fabs(v1 - v2) < (decimal * v1);
}