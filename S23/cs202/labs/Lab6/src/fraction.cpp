/* Will Buziak
 * Lab 6a
 * fraction.cpp
 * for use in the keno lab to manipulate and calculate your statistical probability of matching balls
 */
#include <iostream>
#include <set>
#include "fraction.hpp"
using namespace std;

void Fraction::Clear() {

};

bool Fraction::Multiply_Number(int n){
    if (n < 0) return false;
    if (n == 0) n = 1;
    if (denominator.find(n) == denominator.end()) { // could not find n in the denominator
        numerator.insert(n); // insert into the numerator
    }
    else {
        numerator.erase(n); // could find n in the denominator
        denominator.erase(n); // remove n from both
    }
    return true;
};

bool Fraction::Divide_Number(int n)
{
    if (n < 0) return false;
    if (numerator.find(n) == numerator.end()) { // cannot find n in numerator
        denominator.insert(n); // insert into denominator
    }
    else {
        denominator.erase(n); // if n is in the numerator, remove from both
        numerator.erase(n);
    }
    return true;
};
bool Fraction::Multiply_Factorial(int n)
{
    if (n <= 0) return false;
    int i = 2;
    for (; i <= n; i++) { // i = 2:n
        if (denominator.find(i) == denominator.end()) {
            numerator.insert(i); // if i is not in the denominator, add to numerator
        }
        else {
            denominator.erase(i); // if i is in denominator, erase from both 
            numerator.erase(i);
        }
    }
    return true;
};
bool Fraction::Divide_Factorial(int n)
{
    if (n <= 0) return false;
    int i = 2;
    for (; i <= n; i++) { // i is 2 to n
        if (numerator.find(i) == numerator.end()) { // add to denominator if not in  numerator
            denominator.insert(i);
        }
        else {
            denominator.erase(i); // else erase from both (n/n = 1)
            numerator.erase(i); 
        }
    }
    return true;
};


bool Fraction::Multiply_Binom(int n, int k)
{
    if (n < 0 || k <= 0) return false;
    if (Multiply_Factorial(80 - n) / (Multiply_Factorial(k) * Multiply_Factorial(n - k))) return true;
    else return false;
};

bool Fraction::Divide_Binom(int n, int k)
{
    if (n < 0 || k <= 0) return false;

};

void Fraction::Invert()
{
};

void Fraction::Print() const 
{
    multiset <int>::const_iterator nit;

    if (numerator.size() == 0) cout << 1;
    for (nit = numerator.begin(); nit != numerator.end(); nit++) {
        cout << *nit;
        if (nit != prev(numerator.end())) cout << " * ";
    }

    if (denominator.size() != 0) {
        cout << " / ";
        for (nit = denominator.begin(); nit != denominator.end(); nit++) {
            cout << *nit;
            if (nit != prev(denominator.end())) cout << " / ";
        }
    }
    cout << endl;
};

double Fraction::Calculate_Product() const
{
  double num = 1, dem = 1;
  multiset <int>::const_iterator nit;

  for (nit = numerator.begin(); nit != numerator.end(); nit++) num *= *nit;
  for (nit = denominator.begin(); nit != denominator.end(); nit++) dem *= *nit; 
  
  return num/dem;
};
