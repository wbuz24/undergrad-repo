#include "dlist.hpp"
#include <iostream>
using namespace std;

int main()
{
  string s;
  Dlist l;
  Dnode *d;

  while (getline(cin, s)) l.Insert_Before(s, l.End());
  for (d = l.Rbegin(); d != l.Rend(); d = d->Prev()) {
    cout << d->s << endl;
  }
  return 0;
}
