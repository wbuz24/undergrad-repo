#include <iostream>
#include <stdlib.h>
using namespace std;

main(int argc, char **argv)
{
  int ns, na;
  double s, a;
  double w, h;

  if (argc != 3) {
    cerr << "usage: gen_random_city n-streets n-avenues\n";
    exit(1);
  }

  ns = atoi(argv[1]);
  na = atoi(argv[2]);
  srand48(time(0));

  w = na * .1;
  h = ns * .1;

  for (s = 0; s < ns; s++) {
    for (a = 0; a < na; a++) {
      printf("%4.0lf %4.0lf  %10.6lf %10.6lf  %10.6lf %10.6lf\n",
        s, a, 
        w - (a*.1+drand48()*.1),
        (s*.1+drand48()*.1),
        1+drand48()*40.0,
        1+drand48()*40.0);
    }
  }
}
  
