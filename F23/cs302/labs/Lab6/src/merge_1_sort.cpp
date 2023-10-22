// Will Buziak
// CS302
// Lab 6
// Merge Sort

#include <iostream>
#include "sorting.hpp"
using namespace std;

void recursive_sort(vector <double> &v, vector <double> &temp, int start, int size, int print) {
  size_t j;
  int index, lindex, hindex;
  double tmp;

  if (size == 1) return; // first base case

  if (print) { // Beginning print statement
    printf("B:%6d%6d  ", start, size);
    for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
    cout << endl;
  }

  if (size == 2) { // if there are only two elements
    if (v[start] > v[start + 1]) { // sort them with an if statement
      tmp = v[start]; // swap
      v[start] = v[start + 1];
      v[start + 1] = tmp;
    }
    if (print) { // E call before returning
      printf("E:%6d%6d  ", start, size);
      for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
      cout << endl;
    } 
    return;
  }

  if (size > 2) { // if there are more than 2 elements
    recursive_sort(v, temp, start, size/2, print); // call from start to the end of first half
    recursive_sort(v, temp, start + size/2, size - size/2, print); 

    // after the recursive calls, merge the two into temp
    // set pointers to the start of each half
    index = start;
    lindex = start;
    hindex = start + size/2; // this always chooses the higher half

    // merging
    while (index < start + size) { // you want your lower & upper pointers to be within their respective halves.
      
      if (hindex < start + size && (v[hindex] <= v[lindex] || lindex >= start + size/2)) { // the lower half at index is greater
        temp[index] = v[hindex]; // temp at that index is the lower element
        hindex++; // increment the pointer of the greater half
      }
      else if (lindex < start + size/2 && (v[hindex] > v[lindex] || hindex >= start + size)) { // the lower half is less
        temp[index] = v[lindex]; // temp at index is the lower element
        lindex++; // increment the pointer of the lower half
      }
      index++; // temporary index increments each iteration
    }

    // after merging into tmp, return to v
    for (j = start; j < (size_t) size + start; j++) {
      v[j] = temp[j];
    }
  }  

  if (print) { // E call before printing
    printf("E:%6d%6d  ", start, size);
    for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
    cout << endl;
  }
  return;
}

void sort_doubles(vector <double> &v, bool print){
  vector <double> temp;
  size_t j;

  temp.clear(); // ensure temp is proper size
  temp.resize(v.size());
  temp = v;

  recursive_sort(v, temp, 0, v.size(), print); // recursive call

  printf("                ");
  if (print) { // Print the sorted vector
    for (j = 0; j < v.size(); j++) printf(" %4.2lf", v[j]);
    cout << endl;
  }
  return;
}

