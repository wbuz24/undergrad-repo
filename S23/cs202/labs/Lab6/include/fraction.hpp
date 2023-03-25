#pragma once
#include <set>

/* The Fraction class manages a fraction, where the numerator and the denominator
   are both products of positive integers.  Internally, you will represent the fraction
   as two multisets -- one for the numerator and one for the denominator.  You want to
   make sure that the same number does not appear in both the numerator and denominator.
   When that happens, you should delete the number from both the numerator and the
   denominator.

   You manipulate the product with the first eight methods.  Print() prints the
   fraction and Calculate() calculates the fraction as a double. See the method
   descriptions for more information. 

   For the methods that return a bool, return true when the operation is successful,
   and false if the parameters are bad. */

class Fraction {
  public:
    void Clear();                       // Clear both the numerator and denominator

    bool Multiply_Number(int n);        // Add a number to the numerator
    bool Divide_Number(int n);          // Add a number to the denominator

    bool Multiply_Factorial(int n);     // Add the numbers 2 through n to the numerator
    bool Divide_Factorial(int n);       // Add the numbers 2 through n to the denominator

    bool Multiply_Binom(int n, int k);  // Effect multiplying by n-choose-k
    bool Divide_Binom(int n, int k);    // Effect dividing by n-choose-k

    void Invert();                      // Swap the numerator and denominator

    void Print() const;                 // Print the equation for the fraction (see the lab writeup)

    double Calculate_Product() const;   // Calculate the product as a double.

  protected:
    std::multiset <int> numerator;
    std::multiset <int> denominator;
};
