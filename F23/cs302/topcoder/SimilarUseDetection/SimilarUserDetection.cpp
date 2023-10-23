#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class SimilarUserDetection {
  public:
    string haveSimilar(vector <string> handles);
};

string SimilarUserDetection::haveSimilar(vector <string> H)
{
  size_t i, j;
  unordered_set <string> s;

  for (i = 0; i < H.size(); i++) {
    for (j = 0; j < H[i].size(); j++) {
      if (H[i][j] == '0') H[i][j] = 'O';
      if (H[i][j] == '1' || H[i][j] == 'I') H[i][j] = 'l';
    }
  }

  for (i = 0; i < H.size(); i++) s.insert(H[i]);
  if (s.size() == H.size()) return "Similar handles not found";
  else return "Similar handles found";
}

