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

class Xylophone {
  public:
    int countKeys(vector <int> keys);
};

int Xylophone::countKeys(vector <int> keys)
{
  vector <bool> ans;
  int res = 0;
  size_t i;

  ans.resize(7, 0);
  for (i = 0; i < keys.size(); i++) ans[keys[i] % 7] = 1;
  for (i = 0; i < ans.size(); i++) if (ans[i]) res++;
  return res;
}
