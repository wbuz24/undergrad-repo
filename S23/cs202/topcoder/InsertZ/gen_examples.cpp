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
  int iter, i, j, k, gk, gj;
  int size;
  string init, goal;
  double d;

  for (iter = 0; iter < 100; iter++) {
    init.clear(); goal.clear();
    if (iter < 50) {
      size = (drand48() * 50) + 1;
    } else if (iter < 90) {
      size = (drand48() * 1000) + 1;
    } else {
      size = (drand48() * 100000) + 1;
    }
    for (i = 0; i < size; i++) init.push_back('a' + (int) (drand48() * 24));
    j = drand48() * size;
    k = drand48() * size;
    while (drand48() < .4) goal.push_back('z');
    for (i = 0; i < init.size(); i++) {
      if (i == j) gj = goal.size();
      if (i == k) gk = goal.size();
      goal.push_back(init[i]);
      while (drand48() < .3) goal.push_back('z');
    }
    if (drand48() < .5) {
      d = drand48();
      if (d < .33) {
        j = goal[gj];
        goal[gj] = goal[gk];
        goal[gk] = j;
      } else if (d < .67) {
        for (j = gj; j < goal.size()-1; j++) {
          goal[j] = goal[j+1];
        }
        goal.resize(goal.size()-1);
        if (goal.size() == 0) goal.push_back('a');
      } else {
        goal.push_back('a');
        for (j = gj; j < goal.size()-1; j++) goal[j+1] = goal[j];
        goal[gj] = 'a' + (int) (drand48() * 24);
      }
    }
    printf("%s %s\n", init.c_str(), goal.c_str());
  }
  return 0;
}
