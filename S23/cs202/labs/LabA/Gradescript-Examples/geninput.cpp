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

  for (i = 0; i < nevents; i++) {
    num = drand48()*100;
    if (intree.size() < 10 || num < 10 || num > 90) {
      s = keys[index];
      intree.push_back(s);
      index++;
      printf("INSERT %s %03d-%03d-%04d %03d-%02d-%04d\n", s.c_str(),
         (int) (drand48()*1000), (int) (drand48()*1000), (int) (drand48()*10000),
         (int) (drand48()*1000), (int) (drand48()*100), (int) (drand48()*10000));
    } else if (num < 15) {
      if (intree.size() > 0) {
        j = drand48() * intree.size();
        printf("DELETE %s\n", intree[j].c_str());
      }
    } else if (num < 28) {
      if (intree.size() > 0) {
        j = drand48() * intree.size();
        printf("FIND %s\n", intree[j].c_str());
      }
    } else if (num < 30) {
      printf("FIND %s\n", keys[index].c_str());
      index++;
    } else if (num < 40) {
      printf("PRINT\n");
    } else if (num < 45) {
      printf("VALS\n");
    } else if (num < 47) {
      /* Do nothing. */
    } else if (num < 49) {
      printf("SIZE\n");
    } else if (num < 50) {
      printf("CLEAR\n");
      intree.clear();
    } else if (num < 51) {
      printf("DESTROY\n");
      intree.clear();
    } else if (num < 57) {
      if (commands.find('H') != string::npos) {
        printf("HEIGHT\n");
      }
    } else if (num < 67) {
      if (commands.find('D') != string::npos) {
        if (intree.size() > 0) {
          j = drand48() * intree.size();
          printf("DEPTH %s\n", intree[j].c_str());
        }
      }
    } else if (num < 72) {
      if (commands.find('K') != string::npos) {
        printf("KEYS\n");
      }
    } else if (num < 77) {
      if (commands.find('R') != string::npos) {
        printf("REBALANCE\n");
      }
    } else if (num < 90) {
      if (commands.find('C') != string::npos) {
        printf("PRINT_COPY\n");
      }
    }
  }
  printf("PRINT\n");
  return 0;
}

/*
  INSERT name phone ssn  - Insert the person into the tree.
  FIND name              - Find the person and print them out.
  DELETE person          - Delete the person.
  PRINT                  - Print the keys using the Print() method.
  EMPTY                  - Print whether the tree is empty.
  SIZE                   - Print the tree's size.
  HEIGHT                 - Print the tree's height.
  DEPTH name             - Print the depth of the node whose key is name (-1 if not there).
  KEYS                   - Print the keys using the Ordered_Keys() method.
  VALS                   - Print the vals using the Ordered_Vals() method.
  PRINT_COPY             - Call the copy constructor and call its Print() method.
  REBALANCE              - Turn the tree into a balanced tree by calling the assignment overload.
  CLEAR                  - Clear the tree back to an empty tree.
  DESTROY                - Call the destructor and remake an empty tree.
  QUIT                   - Quit.
  ?                      - Print commands.
*/
