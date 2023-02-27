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

class InsertZ {
  public:
    string canTransform(string init, string goal);
};

string InsertZ::canTransform(string init, string goal)
{
  string ret = "";
  for (size_t i = 0; i < goal.size(); i++) {
    if (goal[i] != 'z') ret += goal[i];  
  }

  if (ret.compare(init) != 0) {
    return "No";
  }
  else return "Yes"; 
}
