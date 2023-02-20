/* This program shows how you read a value from a
   string in hexadecimal using a stringstream. 

   The printf() statement prints the value in
   decimal and then in hexadecimal. */

#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
  string s;
  istringstream ss;
  int i;

  while (cin >> s) {
    ss.clear();
    ss.str(s);
    if (ss >> hex >> i) printf("%d 0x%x\n", i, i);
  }
  return 0;
}
