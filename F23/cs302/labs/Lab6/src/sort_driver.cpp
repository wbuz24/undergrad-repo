/* sort_driver.cpp - A driver for all of the sorting implementations.
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


/* Print the usage string if there is a problem. */

void usage(const char *s)
{
  cerr << "usage: sort_driver size iterations seed double-check(yes|no) print(yes|no)\n";
  if (s != NULL) cerr << s << endl;
  exit(1);
}

int main(int argc, const char **argv)
{
  int size;
  int iterations, it;
  int seed;
  bool dc, print;
  int i;
  int j;
  vector <double> v;

  /* Error check and read the command line arguments. */

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

  /* Create the vector and seed the RNG. */

  v.resize(size);
  srand48(seed);
 
  /* For each iteration, create a random vector and sort it.
     Then, if double-checking is specified, make sure that the
     resulting vector is indeed sorted. */

  for (it = 0; it < iterations; it++) {
    for (i = 0; i < size; i++) v[i] = drand48()*10;
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
  exit(0);
}
