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

class DistanceBetweenStrings {
  public:
    int getDistance(string a, string b, string letterSet);
};

int DistanceBetweenStrings::getDistance(string a, string b, string l)
{
    int diff = 0;

    for (size_t i = 0; i < l.size(); i++) {
        int ac = 0, bc = 0;
        for (size_t j = 0; j < a.size(); j++) {
            if (tolower(a[j]) == tolower(l[i])) ac++;
        }
        for (size_t k = 0; k < b.size(); k++) {
            if (tolower(b[k]) == tolower(l[i])) bc++;
        }
        diff += (ac-bc)*(ac-bc);
    }

    return diff;
}
