#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class SwapAndArithmetic {
  public:
    string able(vector <int> x);
};

string SwapAndArithmetic::able(vector <int> x)
{
  size_t i;
  int diff;
  sort(x.begin(), x.end());
  
  if (x.size() == 1) return "Possible";
  
  else {
    diff = x[1] - x[0];
    for (i = 1; i < x.size(); i++) {
      if ((x[i] - x[i - 1]) != diff) return "Impossible";
    }
  }
  return "Possible";
}
