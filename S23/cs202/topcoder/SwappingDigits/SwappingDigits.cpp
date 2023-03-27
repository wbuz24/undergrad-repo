#include <vector>
#include <string>
#include <iostream>
using namespace std;

class SwappingDigits {
  public:
    string minNumber(string num);
};

string SwappingDigits::minNumber(string num) 
{
  char swap = num[num.size() - 1];
  int index;
  size_t i, j;
  vector <int> index;
  index.resize(10, -1);

  for (i = num.size() - 1; i >= 0; i--) {
       if (num[i] < swap) {
         index[num[i]] = i;
         swap = num[i];
       }
  }

  for (i = 0; i < index.size(); i++) {
       
  }
  

  return num;
}

