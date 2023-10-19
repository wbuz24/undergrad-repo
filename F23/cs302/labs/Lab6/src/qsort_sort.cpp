#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "sorting.hpp"
using namespace std;


int dcomp(const void *v1, const void *v2)
{
  double *d1;
  double *d2;

  d1 = (double *) v1;
  d2 = (double *) v2;
  if (*d1 < *d2) return -1;
  if (*d1 > *d2) return 1;
  return 0;
}

void sort_doubles(vector <double> &v, bool print)
{
  int i, sz;
  double *v2;

  sz = v.size();
  v2 = (double *) malloc(sizeof(double)*sz);
  
  for (i = 0; i < sz; i++) v2[i] = v[i];

  qsort((void *) v2, sz, sizeof(double), dcomp);

  for (i = 0; i < sz; i++) v[i] = v2[i];
  free(v2);
  if (print) {
    for (i = 0; i < sz; i++) printf("%4.2lf ", v[i]);
    cout << endl;
  }
}

