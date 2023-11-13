#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class MyCalendar {
public:
    MyCalendar();
    map <int, bool> Mycal;
    bool book(int start, int end);
};


MyCalendar::MyCalendar() {
  MyCalendar *m;
}


bool MyCalendar::book(int start, int end)
{
  if (Mycal.lower_bound(start)->first < end && !Mycal.lower_bound(start)->second) return false;
  if (Mycal.find(start) != Mycal.end()) return false;
  Mycal.insert(make_pair(start, 1));
  Mycal.insert(make_pair(end, 0));
  return true;
}

int main()
{
  MyCalendar m;
  int start, end;
  bool rv, p;
  string word;
  istringstream ss;
  int seed, num;
  int nt, nf, i;

  while (cin >> word) {
    if (word == "BOOK") {
      if (!(cin >> start >> end)) exit(0);
      printf("%s\n", (m.book(start, end)) ? "TRUE" : "FALSE");
    } else if (word == "RAND" || word == "RAND-P") {
      p = word[word.size()-1] == 'P';
      if (!(cin >> seed >> num)) exit(0);
      srand48(seed);
      nt = 0;
      nf = 0;
      for (i = 0; i < num; i++) {
        start = drand48() * 1000000000;
        end = start + drand48() * 10000000 + 1;
        rv = m.book(start, end);
        if (rv) { nt++; } else { nf++; }
        if (p) printf("%d %d %s\n", start, end, (rv) ? "TRUE" : "FALSE");
      }
      printf("%d %d\n", nt, nf);
    } else {
      printf("Commands must be BOOK, RAND or RAND-P\n");
      exit(1);
    }
  }
  return 0;
}

