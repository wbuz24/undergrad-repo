#include "dlist.hpp"
#include <iostream>
using namespace std;

int main()
{
  string s;
  Dlist l;

  while (getline(cin, s)) l.Push_Front(s);
  while (!l.Empty()) cout << l.Pop_Front() << endl;
  return 0;
}
