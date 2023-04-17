#include <string>
#include <cstring>
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

class AlienAndPassword {
  public:
    int getNumber(string S);
};

int AlienAndPassword::getNumber(string S)
{
  set <string> passwords;
  size_t i;
  string p;

  for (i = 0; i < S.size(); i++) {
    p = S.substr(0,i) + S.substr(i+1); // skip each element of S
    if (passwords.find(p) == passwords.end()) passwords.insert(p); // if the string cannot be found in the set, insert it
  }  
  return passwords.size();
}
