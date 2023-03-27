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
    numerator.clear();
    denominator.clear();
    numerator.insert(1);
};

bool Fraction::Multiply_Number(int n){
    if (n <= 0) return false;
    if (n != 1) { // do nothing if n = 1
        if (denominator.find(n) == denominator.end()) { // could not find n in the denominator
            numerator.insert(n); // insert into the numerator
        }
        else {
           multiset <int>::const_iterator nit = denominator.find(n);
           denominator.erase(nit); // if n is in the numerator, remove from both
           //numerator.erase(*numerator.find(n));
        }
    }
    return true;
};

bool Fraction::Divide_Number(int n)
{
    if (n <= 0) return false;
    if (n != 1) {
        if (numerator.find(n) == numerator.end()) { // cannot find n in numerator
            denominator.insert(n); // insert into denominator
        }
        else {
            multiset <int>::const_iterator nit = numerator.find(n);
            // if n is in the numerator, remove from both
            numerator.erase(nit);
        }
    }

    return true;
};
bool Fraction::Multiply_Factorial(int n)
{
    if (n <= 0) return false;
    int i = 2;
    for (; i <= n; i++) { // i = 2:n
        Multiply_Number(i);
    }
    return true;
};
bool Fraction::Divide_Factorial(int n)
{
    if (n <= 0) return false;
    int i = 2;
    for (; i <= n; i++) { // i is 2 to n
        Divide_Number(i);
    }
    return true;
};


bool Fraction::Multiply_Binom(int n, int k)
{
    if (n <= 0 || k < 0) return false;
    Multiply_Factorial(n);
    Divide_Factorial(k);
    Divide_Factorial(n - k);
    return true;
    
};

bool Fraction::Divide_Binom(int n, int k)
{
    if (n <= 0 || k < 0) return false;
    Divide_Factorial(n);
    Multiply_Factorial(k);
    Multiply_Factorial(n - k);
    return true;
};

void Fraction::Invert()
{
    multiset <int> swap;
    multiset <int>::const_iterator nit;

    for (nit = numerator.begin(); nit != numerator.end(); nit++) { // swap numerator out and erase
      swap.insert(*nit);
    }
    numerator.clear();

    for (nit = denominator.begin(); nit != denominator.end(); nit++) { // insert denominator into numerator
      numerator.insert(*nit);
    }
    denominator.clear();

    for (nit = swap.begin(); nit != swap.end(); nit++) {
      denominator.insert(*nit);
    }
    swap.clear();

};

void Fraction::Print() const 
{
    multiset <int>::const_iterator nit;

    if (numerator.size() == 0) cout << 1;
    for (nit = numerator.begin(); nit != numerator.end(); nit++) {
        cout << *nit;
        if (nit != prev(numerator.end()) && nit != numerator.end()) cout << " * ";
    }

    if (denominator.size() != 0) {
        cout << " / ";
        for (nit = denominator.begin(); nit != denominator.end(); nit++) {
            if (*nit != 1) cout << *nit;
            if (nit != prev(denominator.end()) && nit != denominator.end()) cout << " / ";
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
