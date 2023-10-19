#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include "sorting.hpp"
using namespace std;

void usage(const char *s)
{
  cerr << "usage: sort_driver size iterations seed double-check(yes|no) print(yes|no)\n";
  if (s != NULL) cerr << s << endl;
  exit(1);
}

main(int argc, const char **argv)
{
  vector <double> v;
  double d;

  while (cin >> d) v.push_back(d);
  sort_doubles(v, true);
}
