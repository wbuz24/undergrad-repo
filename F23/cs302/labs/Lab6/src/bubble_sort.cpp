/* bubble_sort.cpp - An implementation of sort_doubles using bubble sort. 
   James S. Plank
   CS302
   September, 2009
   Revised, 2020
 */

#include "sorting.hpp"
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

void sort_doubles(vector <double> &v, bool print)
{
  size_t i, j, n;
  double tmp;

  /* Optionally print out the vector at the beginning. */

  if (print) {
    for (j = 0; j < v.size(); j++) printf("%4.2lf ", v[j]);
    cout << endl;
  }

  n = v.size();

  for (i = 0; i < n-1; i++) {

    /* This is the inner loop. Each time you perform it, you can stop
       one step closer to the beginning of the vector, because the previous
       iteration has placed the element where it belongs. */

    for (j = 0; j < n-i-1; j++) {
      if (v[j] > v[j+1]) {
        tmp = v[j];
        v[j] = v[j+1];
        v[j+1] = tmp;
      }
    }

    /* Optionally print out the vector at the end of each iteration. */

    if (print) {
      for (j = 0; j < v.size(); j++) printf("%4.2lf ", v[j]);
      cout << endl;
    }
  }
}
