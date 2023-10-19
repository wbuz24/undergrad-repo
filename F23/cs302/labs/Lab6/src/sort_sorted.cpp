/* sort_sorted.cpp - A driver that generates "nearly" sorted input.
   James S. Plank
   CS302 Sorting Lecture
   September, 2009
 */
 
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "sorting.hpp"
using namespace std;

void usage(const char *s)
{
  cerr << "usage: sort_driver size iterations seed double-check(yes|no) print(yes|no)\n";
  if (s != NULL) cerr << s << endl;
  exit(1);
}

/* All of the initial code is the same as sort_driver.cpp */

int main(int argc, const char **argv)
{
  int size;
  int iterations, it;
  int seed;
  bool dc, print;
  int i;
  int j;
  vector <double> v;

  if (argc != 6) usage(NULL);

  if (sscanf(argv[1], "%d", &size) != 1 || size <= 0) usage("Bad size\n");
  if (sscanf(argv[2], "%d", &iterations) != 1 || iterations < 0) usage("Bad iterations\n");
  if (sscanf(argv[3], "%d", &seed) != 1) usage("Bad seed\n");
  if (strcmp(argv[4], "yes") == 0) {
    dc = true;
  } else if (strcmp(argv[4], "no") == 0) {
    dc = false;
  } else { 
    usage("Bad double-check\n");
  }
  if (strcmp(argv[5], "yes") == 0) {
    print = true;
  } else if (strcmp(argv[5], "no") == 0) {
    print = false;
  } else { 
    usage("Bad print\n");
  }

  srand48(seed);

  v.resize(size);
 
  for (it = 0; it < iterations; it++) {

    /* The difference is this line -- every element will be within 10 
       slots of its final place in the sorted list. */

    for (i = 0; i < size; i++) v[i] = (((double) i)*.1)+drand48();

    /* The rest is the same. */

    sort_doubles(v, print);
    if (dc) {
      for (i = 0; i < size-1; i++) {
        if (v[i] > v[i+1]) {
          cerr << "V is unsorted at element " << i << endl << endl;
          for (j = 0; j < size; j++) {
            fprintf(stderr, "%d %10.8lf\n", j, v[j]);
          }
          exit(1);
        }
      }
    }
  }
  return 0;
}
