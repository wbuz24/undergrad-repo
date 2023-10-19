/* Using the stl's sort routine to sort. */

#include "sorting.hpp"
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

void sort_doubles(vector <double> &v, bool print)
{
  size_t j;

  sort(v.begin(), v.end());
  if (print) {
    for (j = 0; j < v.size(); j++) printf("%4.2lf ", v[j]);
    cout << endl;
  }
}
