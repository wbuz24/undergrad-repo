#include <iostream>
#include <vector>
#include <cstdio>
#include "sorting.hpp"
using namespace std;

void sort_doubles(vector <double> &v, bool print)
{
  size_t i, j, minindex;
  double tmp;

  if (print) {
    for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
    cout << endl;
  }

  /* Swap the minimum element into element 0 */

  minindex = 0;
  for (i = 1; i < v.size(); i++) if (v[i] < v[minindex]) minindex = i;
  tmp = v[0];
  v[0] = v[minindex];
  v[minindex] = tmp;

  /* Now, I can remove the "(j >= 1)" check in the inner loop: */

  for (i = 1; i < v.size(); i++) {
    tmp = v[i];
    for (j = i; tmp < v[j-1]; j--) v[j] = v[j-1];
    v[j] = tmp;

    if (print) {
      for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
      cout << endl;
    }
  }
}
