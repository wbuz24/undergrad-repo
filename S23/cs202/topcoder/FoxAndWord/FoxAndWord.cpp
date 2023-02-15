#include <string>
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

class FoxAndWord {
    public:
        int howManyPairs(vector <string> words);
};

int FoxAndWord::howManyPairs(vector <string> words)
{
    int result = 0;
    for (int i = 0; i < words.size(); i++) {
        for (int j = 0; j < words[i].size(); j++) {
            string f, s;
            if (i != j) {
                f = words[i].substr(0, j);
                s = words[i].substr(j);
            }
            if ((s + f) == words[j]) {
                result++;
                continue;
            }
        }
    }

    return result;
}
