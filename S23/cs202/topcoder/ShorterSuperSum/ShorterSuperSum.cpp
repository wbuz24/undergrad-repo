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

class ShorterSuperSum {
  public:
    int calculate(int k, int n);
};

int ShorterSuperSum::calculate(int k, int n)
{
  if (k == 0) return n;
  int res = 0, i;
  for (i = 1; i <= n; i++) {
      res += calculate(k - 1, i); 
  }
  return res;
}

