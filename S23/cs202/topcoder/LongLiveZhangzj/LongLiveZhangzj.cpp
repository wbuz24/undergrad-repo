#include <string>
#include <unordered_set>
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

class LongLiveZhangzj {
  public:
    int donate(vector <string> speech, vector <string> words);
};

int LongLiveZhangzj::donate(vector <string> speech, vector <string> words)
{
   unordered_set <string> s;
   int result = 0;
   size_t i = 0;
   for (; i < words.size(); i++) {
     s.insert(words[i]); 
   }

   for (i = 0; i < speech.size(); i++) {
     if (s.find(speech[i]) != s.end()) result++;
   }

   return result;
}
