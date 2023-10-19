#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "pqueue.hpp"
using namespace std;

/* With the binary heap implementation, the
   underlying data structure is a vector, which
   we organize as a heap.  As such, these three
   methods are one-liners. */

       PQueueHeap::PQueueHeap()  { }
size_t PQueueHeap::Size() const  { return h.size(); }
bool   PQueueHeap::Empty() const { return h.empty(); }

/* With Push(), we append the new element to the
   end of the vector, and then percolate up. */

void PQueueHeap::Push(double d) 
{ 
  int i, parent;
  double tmp;

  /* Put the element at the end of the vector. */

  h.push_back(d);

  /* And then percolate up.  i is always
     pointing to the newly added element. */

  i = h.size()-1;
  while (1) {
    if (i == 0) return;
    parent = (i-1)/2;
    if (h[parent] > h[i]) {
      tmp = h[i];
      h[i] = h[parent];
      h[parent] = tmp;
      i = parent;
    } else {
      return;
    }
  }
}

/* I have implemented Percolate_Down as a separate
   protected method, because it is used in two
   places: Pop() and the vector constructor. */

void PQueueHeap::Percolate_Down(size_t index)
{
  size_t lc, rc;
  double tmp;

  /* lc is the left child, and
     rc is the right child. */

  while (1) {                
    lc = index*2+1;
    rc = lc+1;
   
    /* If index is on the bottom of the heap,
       then return, because we can't 
       percolate any more. */

    if (lc >= h.size()) return;

    /* With this code, either there is no
       right child, or the left child is
       smaller than the right child.  In 
       this case, you need to compare the
       element at index with the left child. */

    if (rc == h.size() || h[lc] <= h[rc]) {
      if (h[lc] < h[index]) {
        tmp = h[lc];
        h[lc] = h[index];
        h[index] = tmp;
        index = lc;
      } else {
        return;
      }

    /* Otherwise, we compare the element at
       index with the right child. */

    } else if (h[rc] < h[index]) {
      tmp = h[rc];
      h[rc] = h[index];
      h[index] = tmp;
      index = rc;
    } else {
      return;
    }
  }
}

/* With Pop(), after we error check, we
   move the last element to the root of
   the heap, and percolate down. */

double PQueueHeap::Pop() 
{
  double retval;
  
  if (h.empty()) {
    throw (string) "Called Pop() on an empty PQueue";
  }
  retval = h[0];
  h[0] = h[h.size()-1];
  h.pop_back();
  if (h.size() == 0) return retval;
  Percolate_Down(0);
  return retval;
}

/* The vector constructor calls Percolate_Down()
   on all non-leaf elements, going from the bottom 
   of the heap to the top. */

PQueueHeap::PQueueHeap(const vector <double> &v) 
{ 
  int i;

  h = v;

  for (i = (int) h.size()/2-1; i >= 0; i--) Percolate_Down(i);
}

/* Print is straightforward. */

void PQueueHeap::Print() const
{
  size_t i;

  for (i = 0; i < h.size(); i++) {
    if (i != 0) cout << " ";
    cout << h[i];
  }
  cout << endl;
}
