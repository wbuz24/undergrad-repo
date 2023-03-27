#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

unsigned int djb_hash(const string &s)
{
  size_t i;
  unsigned int h;

  h = 5381;

  for (i = 0; i < s.size(); i++) {
    h = (h << 5) + h + s[i];
  }
  return h;
}

int main()
{
  unsigned int h;
  srand48(time(0));
  string s, duh;
  size_t i;

  for (i = 0; i < 10; i++) duh.push_back('0'+i);
  for (i = 0; i < 26; i++) duh.push_back('A'+i);
  for (i = 0; i < 26; i++) duh.push_back('a'+i);
  
  while (1) {
    s.clear();
    for (i = 0; i < 14; i++) s.push_back(duh[lrand48()%duh.size()]);
    h = djb_hash(s);
    if (h % 17 == 0 || h % 13 == 0) cout << s << endl;
  }
}
