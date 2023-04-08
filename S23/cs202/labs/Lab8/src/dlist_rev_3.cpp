#include "dlist.hpp"
#include <iostream>
using namespace std;

int main()
{
  string s;
  Dlist l;
  Dnode *d;

  while (getline(cin, s)) l.Push_Front(s);
  for (d = l.Begin(); d != l.End(); d = d->Next()) cout << d->s << endl;
  return 0;
}
