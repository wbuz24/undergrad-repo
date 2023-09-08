// Will Buziak
// cs302
// Lab 2
// Binary search on all numbers of varying types

#include <iostream>
#include <vector>
#include "lab_2.hpp"
using namespace std;

unsigned long long whats_my_number_ll()
{
  unsigned long long l, h, m;

  l = 0;
  h = 0 - 1; // 2^64 - 1 using overflow

  while (h > 1) {
    m = l + h/2; // middle

    if (am_i_greater_ll(m)) h /= 2; // discard upper
    else {
      l += h/2; // discard lower
      h -= h/2;
    }
  }
  return l;
}

double whats_my_number_d()
{
  double l, h, m;

  l = 0;
  h = 1e9; // size

  while (h >= 1e-9) {
    m = l + h/2; // middle

    if (am_i_greater_d(m)) h /= 2; // discard upper
    else {
      l += h/2; // discard lower
      h -= h/2;
    }
  }
  return l;
}

unsigned int optimal()
{
  unsigned int l, h, m;

  l = 0;
  h = -1;

  while (h > 1) {
    m = l + h/2; 
    if (func(m) > func(m - 1)) { // discard the bottom
      l += h/2;
      h -= h/2;
    }
    else {
      h /= 2;     // Throw away the top half
    }
  }
  return l;
}
