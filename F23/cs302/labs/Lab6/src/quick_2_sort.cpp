// Will Buziak
// CS302
// Lab 6
// Quick Sort

#include <iostream>
#include "sorting.hpp"
using namespace std;

void median(vector <double> &v, int start, int size, bool print) {
  int l, m, h; // low, medium & high indices
  size_t j;
  double tmp;

  l = start;
  m = start + size/2;
  h = start + size - 1;

  // find the median element of the three & swap it to the v[start]
  if ((v[m] > v[l] && v[m] < v[h]) || (v[m] < v[l] && v[m] > v[h])) { 
    // the middle is the median
    tmp = v[l];
    v[l] = v[m];
    v[m] = tmp;
  }
  else if((v[h] > v[l] && v[h] <= v[m]) || (v[h] < v[l] && v[h] > v[m])) {
    // the higher element is the median
    tmp = v[l];
    v[l] = v[h];
    v[h] = tmp;
  }

  if (v[h] == v[l] && v[h] > v[m]) { // high & low are greater than the middle
    tmp = v[h];
    v[h] = v[l]; // swap for higher index
    v[l] = tmp;
  }
  else if (v[m] == v[l] && v[m] > v[h]) { // middle & low are greater than the high
    tmp = v[m]; // swap for middle index
    v[m] = v[l];
    v[l] = tmp;
  }
  else if (v[m] == v[h] && v[m] > v[l]) { // middle & higher are greater than the low
    tmp = v[h];
    v[h] = v[l];
    v[l] = tmp;
  }
  // print
  if (print) { // Beginning print statement
    printf("M:%6d%6d  %4.2f", start, size, v[start]);
    for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
    cout << endl;
  }

  return;
}

void recursive_sort(vector <double> &v, int start, int size, bool print) {
  size_t j;
  int l, r;
  double tmp;

  if (size == 1) return; // first base case

  if (print) { // Beginning print statement
    printf("S:%6d%6d      ", start, size);
    for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
    cout << endl;
  }

  if (size == 2) { // if there are only two elements
    if (v[start] > v[start + 1]) { // sort them with an if statement
      tmp = v[start]; // swap
      v[start] = v[start + 1];
      v[start + 1] = tmp;
    }
    return;
  }

  if (size > 2) { // if there are more than 2 elements
    // Find the median of three & set the pivot
    median(v, start, size, print);
    l = start + 1;
    r = start + size - 1;

    // presort the vector
    while (l < r) { // you want your lower & upper pointers to be within their respective halves.
      while (v[l] < v[start] && l < start + size - 1) l++; // increment the left pointer
      while (v[r] > v[start] && r > start) r--; // decrement the right pointer
      if (l == r) { // if L == R
       if (v[l] < v[start]) l--; // decrement the left pointer
       else l++;
      }
      if (l < r) { // if not done, swap the elements
        tmp = v[l];
        v[l] = v[r];
        v[r] = tmp;
      }
    }

    // after we are finished, swap the pivot with the last element of the left set
    tmp = v[start];
    v[start] = v[l - 1];
    v[l - 1] = tmp;

    if (print) { // Pivot call before recursive calls
      printf("P:%6d%6d  %4d", start, size, l - 1);
      for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
      cout << endl;
    }

    recursive_sort(v, start, l - start - 1, print); // call from start to the end of first half
    recursive_sort(v, l, start + size - l, print); 
  }

  return;
}

void sort_doubles(vector <double> &v, bool print){
  size_t j;

  recursive_sort(v, 0, v.size(), print); // recursive call

  printf("                    ");
  if (print) { // Print the sorted vector
    for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
    cout << endl;
  }
  return;
}

