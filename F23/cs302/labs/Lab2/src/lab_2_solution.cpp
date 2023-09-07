#include <iostream>
#include <vector>
#include "lab_2.hpp"
using namespace std;

unsigned long long whats_my_number_ll()
{
  unsigned long long l, h, m;

  l = 0;
  h = 0 - 2; // 2^64 - 1 using overflow

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
  h = 1000000000; // billion

  while (h > 1) {
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
  return 0;
}
