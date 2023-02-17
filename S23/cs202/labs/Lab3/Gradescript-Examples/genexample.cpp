#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
  int num;
  int w, h;
  int nc;
  double c;
  int i, rr, rc, rrs, rcs, tmp;

  cin >> num >> w >> h;

  srand48(num);

  nc = drand48() * 7 + 2;
  printf("READ input.pgm\n");
  for (i = 0; i < nc; i++) {
    c = drand48() * 5;
    if (c < 1) {
      printf("CW\n");
      tmp = w;
      w = h;
      h = tmp;
    } else if (c < 2) {
      printf("CCW\n");
      tmp = w;
      w = h;
      h = tmp;
    } else if (c < 3) {
      rr = (drand48() * .2 * (double) h );
      rc = (drand48() * .2 * (double) w );
      rrs = h - (drand48() * .2 * (double) h);
      rcs = w - (drand48() * .2 * (double) w);
      printf("CROP %d %d %d %d\n", rr, rc, rrs, rcs);
      w = rcs;
      h = rrs;
    } else if (c < 4) {
      rr = (drand48() * 14 + 1);
      rc = (drand48() * 256);
      printf("PAD %d %d\n", rr, rc);
      w += (rr*2);
      h += (rr*2);
    } else {
      rr = (drand48() * 4 + 1);
      rc = (drand48() * 4 + 1);
      printf("PANEL %d %d\n", rr, rc);
      h *= (rr);
      w *= (rc);
    }
  }
  printf("WRITE output.pgm\n");
  return 0;
}
