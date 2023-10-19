/* selection_sort.cpp - An implementation of sort_doubles using selection sort. 
   James S. Plank
   CS302
   September, 2009
   Revised 2020
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include "sorting.hpp"
using namespace std;

void sort_doubles(vector <double> &v, bool print)
{
  int i, j, k, n;
  double tmp;
  int minindex;

  n = v.size();

  /* Optionally print the vector before sorting */

  if (print) {
    for (k = 0; k < n; k++) printf("%4.2lf ", v[k]);
    cout << endl;
  }

  /* Outer loop.  At each of these iterations, we
     are going to find the smallest element from
     index i to the end, and swap it with the
     element in index i.  */

  for (i = 0; i < n-1; i++) {
    
    /* Put the index of the smallest element 
       starting at index i in minindex. */

    minindex = i;
    for (j = i+1; j < n; j++) {
      if (v[j] < v[minindex]) {
        minindex = j;
      }
    }

    /* Now swap v[minindex] with v[i] */

    tmp = v[i];
    v[i] = v[minindex];
    v[minindex] = tmp;
      
    /* Optionally print the vector. */

    if (print) {
      for (k = 0; k < n; k++) printf("%4.2lf ", v[k]);
      cout << endl;
    }
  }
}
