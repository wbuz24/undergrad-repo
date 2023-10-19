/* insertion_1_sort.cpp - Insertion sort implemented straight from its definition.
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
  size_t i, j;
  double tmp;

  /* Optionally print the vector */

  if (print) {
    for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
    cout << endl;
  }

  for (i = 1; i < v.size(); i++) {

    /* Inner loop -- while element i is out of place,  
       swap it with the element in front of it. */

    for (j = i; j >= 1 && v[j] < v[j-1]; j--) {
      tmp = v[j-1];
      v[j-1] = v[j];
      v[j] = tmp;
    }

    /* Optionally print the vector */

    if (print) {
      for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
      cout << endl;
    }
  }
}
