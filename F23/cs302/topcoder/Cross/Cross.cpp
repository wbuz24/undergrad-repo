#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Cross {
  public:
    string exist(vector <string> board);
};

string Cross::exist(vector <string> B)
{
  size_t i, j;

  for (i = 1; i < B.size() - 1; i++) {
    for (j = 1; j < B[i].size() - 1; j++) {
      if (B[i][j] == '#' && B[i - 1][j] == '#' && B[i][j - 1] == '#' && B[i][j + 1] == '#' && B[i + 1][j] == '#') return "Exist";
    }
  }
  return "Does not exist";
}

