#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

void usage(string s)
{
  fprintf(stderr, "usage: random_hero_gen number-of-names x_limit y_limit hp_limit\n");
  if (s != "") fprintf(stderr, "   %s\n", s.c_str());
  exit(1);
}
int main(int argc, char **argv)
{
  int xl, yl, mh, h, tnames, i;
  vector <string> names;
  vector <string> classes;
  ifstream f;
  set <string> used;
  string s;

  srand48(time(0));

  if (argc != 5) usage("");
  tnames = atoi(argv[1]); if (tnames <= 0) usage("Bad number of names");
  xl     = atoi(argv[2]); if (xl <= 0) usage("Bad x_limit");
  yl     = atoi(argv[3]); if (yl <= 0) usage("Bad y_limit");
  mh     = atoi(argv[4]); if (mh <= 0) usage("Bad hp_limit");

#include "names.h"
#include "classes.h"

  for (i = 0; i < tnames; i++) {
    if (i == 0) {
      s = "Urgosa_the_Healing_Shaman";
    } else {
      do {
        s = names[lrand48()%names.size()];
        s += "_the_";
        s += classes[lrand48()%classes.size()];
      } while (used.find(s) != used.end());
    }
    h = lrand48()%mh + 1;
    printf("%5ld %5ld %5ld %5d %s\n", 
       lrand48()%(2*xl+1) - xl,
       lrand48()%(2*yl+1) - yl,
       lrand48()%(h+1),
       h, s.c_str());
  }
  exit(0);
}
