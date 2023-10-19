/* bucket_2_sort.cpp - This is identical to bucket_1_sort.cpp, except the size of the
                       temporary array is doubled.
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
  int sz, v2sz;
  int index;
  double val;
  double *v2;
  int hind, lind, done, i, j;

  sz = v.size();
  v2sz = (int) (sz * 2);

  v2 = (double *) malloc(sizeof(double)*(v2sz+1));
  for (i = 0; i < (v2sz+1); i++) v2[i] = -1;

  for (i = 0; i < sz; i++) {
    val = (v[i] / 10.0 * v2sz);
    index = (int) val;
    if (v2[index] == -1) {
      v2[index] = v[i];
    } else {
      hind = index+1;
      lind = index-1;
      done = 0;
      while(!done) {
        if (hind < v2sz && v2[hind] == -1) {
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
  j = 0;
  i = 0;
  while (j < sz) {
    if (v2[i] != -1) {
      v[j] = v2[i];
      j++;
    }
    i++;
  }

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
  free(v2);
}
