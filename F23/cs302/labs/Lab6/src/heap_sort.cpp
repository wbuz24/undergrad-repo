/* heap_sort.cpp - An implementation of sort_doubles using priority queues from 
                   the Priority Queue lecture notes.
   James S. Plank
   CS302
   September, 2009
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include "sorting.hpp"
#include "pqueue.hpp"
using namespace std;

void sort_doubles(vector <double> &v, bool print)
{
  size_t i, j;
  PQueue *heap;

  heap = new PQueueHeap(v);

  if (print) {
    for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
    printf("   ");
    heap->Print();
    cout << endl;
  }

  for (i = 0; i < v.size(); i++) {
    v[i] = heap->Pop();
    if (print) {
      for (j = 0; j < v.size(); j++) printf("%.2lf ", v[j]);
      printf("   ");
      heap->Print();
      cout << endl;
    }
  }
  delete heap;
}

