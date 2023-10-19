/* null_sort.cpp - Baseline control for the sorting example.
   James S. Plank
   CS302
   September, 2009
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include "sorting.hpp"
using namespace std;


void sort_doubles(vector <double> &v, bool print)
{
  size_t j;

  if (print) {
    for (j = 0; j < v.size(); j++) printf("%4.2lf ", v[j]);
    cout << endl;
  }

  return;
}
