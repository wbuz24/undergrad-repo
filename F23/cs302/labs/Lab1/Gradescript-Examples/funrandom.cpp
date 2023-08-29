#include <string>
#include <cstring>
#include <cstdio>
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
  SVec names;
  int i;
  SSmap ssm;
  SSmit sit;
  string ar, al, tn, k, s;
  char buffer[100];

  names.push_back("Cher");
  names.push_back("Madonna");
  names.push_back("Queen");
  names.push_back("Fabio");
  names.push_back("Thor");
  names.push_back("Baby_Daisy");

  srand48(time(0));

  for (i = 0; i < 500; i++) {
    ar = names[lrand48()%names.size()];
    al = names[lrand48()%names.size()];
    sprintf(buffer, "%ld", lrand48()%80+1);
    tn = buffer;
    k = ar;
    k += ":";
    k += al;
    k += ":";
    k += tn;

    s = names[lrand48()%names.size()];
    s += " ";
    do {
      sprintf(buffer, "%ld:%02ld", lrand48()%12, lrand48()%60);
    } while (strcmp(buffer, "0:00") == 0);
    s += buffer;
    s += " ";
    s += ar;
    s += " ";
    s += al;
    s += " ";
    s += names[lrand48()%names.size()];
    s += " ";
    s += tn;
    ssm[k] = s;
  }

  IT(sit, ssm) cout << sit->second << endl;
}
