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

class LandMines {
  public:
    int numClear(vector <string> layout);
    vector <int> adj;
    vector <int> states;
};

int LandMines::numClear(vector <string> layout)
{
  size_t i, j, k;
  bool set = 1;

  states.clear();
  states.resize(layout.size() * layout[0].size());

  for (i = 0; i < layout.size() * layout[0].size(); i++) {
    states[i] = layout[i / layout[0].size()][i % layout[0].size()];
  }

  adj.clear();
  adj.resize(states.size() * 4, -1);
  
  for (i = 0; i < layout.size(); i++) {
    set = 1;
    for (j = i + 1; j < layout[0].size(); j++) { // check to the right
      if (states[i*layout.size() + j] == 'M') set = 0;
      
      for (k = i; i < layout.size(); i++) { // check above
        if (states[k*layout.size() + j] == 'M') set = 0;
      }
      if (set) adj[i] = k * layout.size() + j; // set link above
      else set = 1;

      for (k = i; k >= 0; k--) { // check below
        if (states[k*layout.size() + j] == 'M') set = 0;
      }
      if (set) adj[i] = k * layout.size() + j; // set link below
      else set = 1;
    }
    
    if (set) adj[i] = i + 1; // link to the right

    for (j = i - 1; j >= 0; j--) { // check to the left
      if (states[i*layout.size() + j] == 'M') set = 0;

      
      for (k = i; i < layout.size(); i++) { // check above
        if (states[k*layout.size() + j] == 'M') set = 0;
      }
      if (set) adj[i] = k * layout.size() + j; // set link above
      else set = 1;

      for (k = i; k >= 0; k--) { // check below
        if (states[k*layout.size() + j] == 'M') set = 0;
      }
      if (set) adj[i] = k * layout.size() + j; // set link below
      else set = 1;
    }
    if (set) adj[i] = i - 1; // link to the left
  }


  // perform DFS, summing the components connected to node zero.
  // use the states field for visited

  return 0;
}

