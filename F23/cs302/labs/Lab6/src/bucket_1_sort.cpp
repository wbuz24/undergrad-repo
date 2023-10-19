/* bucket_1_sort.cpp - Taking advantage of the fact that we know the probability distribution
                       of our input, to sort with bucket sort.
   James S. Plank
   CS302
   September, 2009
   Revised 2020
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "sorting.hpp"
using namespace std;

void insertion_sort(vector <double> &v)
{
  int i, j, sz, index;
  double tmp;

  sz = v.size();
  tmp = v[0];
  index = 0;
  for (i = 1; i < sz; i++) {
    if (v[i] < tmp) {
      tmp = v[i];
      index = i;
    }
  }
  if (index != 0) {
    v[index] = v[0];
    v[0] = tmp;
  }
  
  for (i = 1; i < sz; i++) {
    tmp = v[i];
    for (j = i-1; tmp < v[j]; j--) {
      v[j+1]  = v[j];
    }
    v[j+1] = tmp;
  }
}

void sort_doubles(vector <double> &v, bool print)
{
  int sz;
  int index, j;
  double val;
  double *v2;
  int hind, lind, done, i;

  sz = v.size();

  /* Allocate a new array, and set every entry to -1. */

  v2 = (double *) malloc(sizeof(double)*sz);
  for (i = 0; i < sz; i++) v2[i] = -1;

  /* For each element, find out where you think it will go.
     If that index is empty, put it there. */

  for (i = 0; i < sz; i++) {
    val = (v[i] * sz/10.0);
    index = (int) val;
    if (v2[index] == -1) {
      v2[index] = v[i];

    /* Otherwise, check nearby, above and below, until
       you find an empty element. */

    } else {
      hind = index+1;
      lind = index-1;
      done = 0;
      while(!done) {
        if (hind < sz && v2[hind] == -1) {
          v2[hind] = v[i];
          done = 1;
        } else {
          hind++;
        }
        if (!done && lind >= 0 && v2[lind] == -1) {
          v2[lind] = v[i];
          done = 1;
        } else {
          lind--;
        }
      }
    } 
  }

  /* At the end, copy this new vector back to the
     old one, free it, and call insertion sort to 
     "clean up" the vector. */

  for (i = 0; i < sz; i++) v[i] = v2[i];
  free(v2);

  if (print) {
    cout << "Before Insertion Sort\n";
    for (j = 0; j < sz; j++) printf("%.2lf ", v[j]);
    cout << endl;
  }

  insertion_sort(v);

  if (print) {
    cout << "After Insertion Sort\n";
    for (j = 0; j < sz; j++) printf("%.2lf ", v[j]);
    cout << endl;
  }
}
