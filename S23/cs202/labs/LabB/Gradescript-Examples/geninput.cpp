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

int main()
{
  int nevents;
  int i, j;
  string commands, s;
  vector <string> keys;
  string tmp;
  int index;
  vector <string> intree;
  int num;
  bool dontprint;
  
  srand48(time(0));

  if (!(cin >> nevents >> commands)) return 1;

  while (cin >> s) keys.push_back(s);
  for (i = 0; i < keys.size(); i++) {
    j = drand48() * (keys.size()-i);
    tmp = keys[keys.size()-i-1];
    keys[keys.size()-i-1] = keys[j];
    keys[j] = tmp;
  }

  index = 0;
  dontprint = true;

  for (i = 0; i < nevents; i++) {
    num = drand48()*80;
    if (intree.size() < 10 || num < 10 || num > 90) {
      s = keys[index];
      intree.push_back(s);
      index++;
      printf("INSERT %s %03d-%03d-%04d %03d-%02d-%04d\n", s.c_str(),
         (int) (drand48()*1000), (int) (drand48()*1000), (int) (drand48()*10000),
         (int) (drand48()*1000), (int) (drand48()*100), (int) (drand48()*10000));
        printf("IS_AVL\n");
      dontprint = false;
    } else if (num < 15) {
      if (commands.find('E') != string::npos) {
        if (intree.size() > 0) {
          j = drand48() * intree.size();
          printf("DELETE %s\n", intree[j].c_str());
          printf("IS_AVL\n");
        }
      }
      dontprint = false;
    } else if (num < 28) {
      if (intree.size() > 0) {
        j = drand48() * intree.size();
        printf("FIND %s\n", intree[j].c_str());
      }
    } else if (num < 30) {
      printf("FIND %s\n", keys[index].c_str());
      index++;
    } else if (num < 40) {
      if (!dontprint) printf("PRINT\n");
      dontprint = true;
    } else if (num < 45) {
      printf("VALS\n");
    } else if (num < 47) {
      /* Do nothing. */
    } else if (num < 49) {
      printf("SIZE\n");
    } else if (num < 50) {
      if (commands.find('L') != string::npos) {
        printf("CLEAR\n");
        printf("IS_AVL\n");
        intree.clear();
        dontprint = false;
      }
    } else if (num < 51) {
      if (commands.find('D') != string::npos) {
        printf("DESTROY\n");
        printf("IS_AVL\n");
        intree.clear();
        dontprint = false;
      }
    } else if (num < 57) {
      if (commands.find('H') != string::npos) {
        printf("HEIGHT\n");
      }
    } else if (num < 62) {
      if (commands.find('K') != string::npos) {
        printf("KEYS\n");
      }
    } else if (num < 67) {
      if (commands.find('A') != string::npos) {
        printf("ASSIGNMENT\n");
        printf("IS_AVL\n");
        dontprint = false;
      }
    } else if (num < 80) {
      if (commands.find('C') != string::npos) {
        printf("PRINT_COPY\n");
        printf("IS_AVL\n");
      }
    }
  }
  if (!dontprint) printf("PRINT\n");
  return 0;
}
