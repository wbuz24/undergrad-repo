/* set_sort.cpp - An implementation of sort_doubles using multisets from the STL.
   James S. Plank
   CS302
   September, 2009
   Revised 2020
 */

#include "sorting.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
using namespace std;

void sort_doubles(vector <double> &v, bool print)
{
  multiset <double> s;
  size_t i;
  multiset <double>::iterator sit;

  for (i = 0; i < v.size(); i++) s.insert(v[i]);
  i = 0;
  for (sit = s.begin(); sit != s.end(); sit++) {
    v[i] = *sit;
    i++;
  }
  if (print) {
    for (i = 0; i < v.size(); i++) printf("%4.2lf ", v[i]);
    cout << endl;
  }

}
