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

  while (cin >> s) lns.push_back(s);
  
  srand48(time(0));

  it = lrand48()%400+1;
  for (i = 0; i < it; i++) {
    jt = lrand48()%15;
    k = lrand48()%5+1;
    for (nl = 0; nl < k; nl++) cout << " " ;
    for (j = 0; j < jt; j++) {
      k = lrand48()%5+1;
      for (nl = 0; nl < k; nl++) cout << " " ;
      if (drand48() < .5) {
        cout << lns[lrand48()%lns.size()];
      } else {
        k = lrand48()%8;
        printf("%.*lf", k, drand48()*1000.0 - 500.0);
      }
    }
    cout << endl;
  }

}
