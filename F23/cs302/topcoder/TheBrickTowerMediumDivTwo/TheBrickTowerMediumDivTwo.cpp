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

class TheBrickTowerMediumDivTwo {
  public:
    vector <int> find(vector <int> heights);
};

vector <int> TheBrickTowerMediumDivTwo::find(vector <int> heights)
{
  vector <int> rv;
  int u, iter = 0;
  rv.clear();

  while (next_permutation(heights.begin(), heights.end())) {
    u = heights[iter] - heights[iter+1];

    rv.push_back(u);

    iter++;
  }

  return rv;
}
