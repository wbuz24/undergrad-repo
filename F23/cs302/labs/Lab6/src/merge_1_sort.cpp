// Will Buziak
// CS302
// Lab 6
// Merge Sort

#include <iostream>
#include "sorting.hpp"
using namespace std;

void recursive_sort(vector <double> &v, vector <double> &temp, int start, int size, int print) {
  size_t j;
  int index;
  double tmp;
  double *low, *high;
  (void) temp;

  if (size == 1) return;
  
  if (print) {
      printf("B:%5d%5d      ", start, size);
      for (j = 0; j < v.size(); j++) printf("%4.2lf ", v[j]);
      cout << endl;
  }

  if (size == 2) { // if there are only two elements
   if (v[start] < v[start + 1]) { // sort them with an if statement
      tmp = v[start];
      v[start] = v[start + 1];
      v[start + 1] = tmp;
    }
    if (print) { // E call before returning
      printf("E:%5d%5d      ", start, size);
      for (j = 0; j < v.size(); j++) printf("%4.2lf ", v[j]);
      cout << endl;
    } 
    return;
  }

  if (size > 2) { // if there are more than 2 elements
    recursive_sort(v, temp, start, size/2, print); // call of the two halves
    recursive_sort(v, temp, size - size/2, size/2, print); // deals with odd sizes
    
    temp.clear();
    temp.resize(v.size());
    temp = v;
    // after the recursive calls, merge the two into temp
    // set pointers to the start of each half
    index = start;
    low = &v[start];
    high = &v[size - size/2];

    while (low < &v[size - size/2] && high <= &v[size - 1] && index > temp.size()) { // you want your lower & upper pointers to be within their respective halves.
      if (*high < *low) { // the lower half at index is greater
        temp[index] = *high; // temp at that index is the lower element
        if (high < &v[size - 1]) high++; // increment the pointer of the greater half
      }
      else { // the lower half is less
        temp[index] = *low; // temp at index is the lower element
        if (low < &v[size - size/2]) low++; // increment the pointer of the lower half
      }
      index++; // increment index each iteration
    }


    // after merging into tmp, return to v
    for (j = 0; j < temp.size(); j++) {
      v[j] = temp[j];
    }

  } 

  if (print) { // E call before printing
      printf("E:%5d%5d      ", start, size);
      for (j = 0; j < v.size(); j++) printf("%4.2lf ", v[j]);
      cout << endl;
  }
  return;
}

void sort_doubles(vector <double> &v, bool print){
  vector <double> temp;

  temp.clear();
  recursive_sort(v, temp, 0, v.size(), print);
  return;

}

