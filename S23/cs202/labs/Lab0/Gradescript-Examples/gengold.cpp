#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define VIT(i, v) for (i = 0; i < v.size(); i++) 
#define IT(it, ds) for (it = ds.begin(); it != ds.end(); it++)
#define FUP(i, n) for (i = 0; i < n; i++)

typedef map<int, string> ISmap;
typedef map<int, int> IImap;
typedef map<string, int> SImap;
typedef map<string, string> SSmap;

typedef ISmap::iterator ISmit;
typedef IImap::iterator IImit;
typedef SSmap::iterator SSmit;
typedef SImap::iterator SImit;

typedef vector <int> IVec;
typedef vector <double> DVec;
typedef vector <string> SVec;

main()
{
  int nl, nc, i, j, k, it, jt;
  SVec lns;
  string s;
  
  srand48(time(0));

  nl = lrand48()%10+10;

  for (i = 0; i < nl; i++) {
    nc = lrand48()%10+40;
    for (j = 0; j < nc; j++) {
      k = lrand48()%3;
      if (k == 0) printf(".");
      if (k == 1) printf("-");
      if (k == 2) printf("%c", 'A' + lrand48()%26);
    }
    printf("\n");
  }
}
