#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class TreesAndBrackets {
  public:
    string check(string t1, string t2);
};

string TreesAndBrackets::check(string t1, string t2)
{
  if (t1 == t2) return "Possible";
  if (t1.size() < t2.size()) return "Impossible";
  TreesAndBrackets(t1, t2);
  
  return "Impossible";
}
