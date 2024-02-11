#include <iostream>
#include <string>
#include <sstream>
using namespace std;

char compress(int val)
{
  if(0 <= val && val <= 9)
    return '0' + val;
  if(10 <= val && val <= 35)
    return 'a' + val - 10;
  if(36 <= val && val <= 61)
    return 'A' + val - 36;
  if(val == 62)
    return '#';
  if(val == 63)
    return '@';
  return -1; //shouldn't happen
}

int main()
{
  string s;

  while(getline(cin, s))
  {
    stringstream ss(s);
    char c;
    int count = 0;
    int val = 0;

    while(ss >> c)
    {
      val |= (c - '0') << count++;

      count %= 6;
      if(count == 0)
      {
        cout << compress(val);
        val = 0;
      }
    }

    if (count != 0) cout << compress(val);
    cout << endl;
  }
}
