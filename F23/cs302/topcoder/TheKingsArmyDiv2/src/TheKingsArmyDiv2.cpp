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

class TheKingsArmyDiv2 {
  public:
    int getNumber(vector <string> state);
};

int TheKingsArmyDiv2::getNumber(vector <string> state)
{
  size_t i, j;
  for (i = 0; i < state.size(); i++) {
    for (j = 0; j < state[i].size(); j++) {
      if (state[i][j] == 'H') {
        if (state[i+1][j] == 'H' && (i+1) <= state.size()) return 0;
        if (state[i][j+1] == 'H' && (j+1) <= state[i].size()) return 0;
        else return 1;
      }
    }
  }
  return 2;
}

