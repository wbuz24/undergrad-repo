#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
  string l;
  string m;
 
  m = "";
  while (getline(cin, l)) {
    if (l == "") {
      printf("%s\n", m.c_str());
      m = "";
    } else {
      if (m != "") m.push_back(' ');
      m += l;
    }
  }
  exit(0);
}
