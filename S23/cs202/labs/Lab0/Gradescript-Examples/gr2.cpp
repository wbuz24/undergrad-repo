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
  int nl, nc, i, j, k;
  
  srand48(time(0));

  printf("%.3lf %.3lf %d\n", drand48()*1000, drand48()*10.0, lrand48()%100+1);
}
