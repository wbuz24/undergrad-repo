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

class MiddleCode {
  public:
    string encode(string s);
};

string MiddleCode::encode(string s)
{
  string t = "";

  while (s.size() > 0) {
    if (s.size() % 2 == 0) {
        int upper, lower;
        

        upper = s.size() / 2;
        lower = (s.size() / 2) - 1;

        if (s[lower] < s[upper]) {
            t+= s[lower];
            s.erase(s.begin() + lower);
        }
        else {
            t+= s[upper];
            s.erase(s.begin() + upper);
        }
    }

    else {
        int index = s.size() / 2;

        t+= s[index];
        s.erase(s.begin() + index);
    }
  }


    return t + "\n";
}
