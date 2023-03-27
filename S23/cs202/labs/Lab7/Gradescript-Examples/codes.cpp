#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

unsigned int djb_hash(string &s)
{
  int i;
  unsigned int h;

  h = 5381;

  for (i = 0; i < s.size(); i++) {
    h = (h << 5) + h + s[i];
  }
  return h;
}

main()
{
  unsigned int h;
  srand48(time(0));
  string s, duh;
  int i;

  for (i = 0; i < 10; i++) duh.push_back('0'+i);
  for (i = 0; i < 26; i++) duh.push_back('A'+i);
  for (i = 0; i < 26; i++) duh.push_back('a'+i);
  
  while (1) {
    s.clear();
    for (i = 0; i < 14; i++) s.push_back(duh[lrand48()%duh.size()]);
    h = djb_hash(s);
    if (h % 17 == 0) {
      cout << 17 << " " << s << endl;
    } else if (h % 13 == 0) {
      cout << 13 << " " << s << endl;
    } else {
      cout << "XX" << " " << s << endl;
    }
  }
}
