#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define VIT(i, v) for (i = 0; i < v.size(); i++) 
#define IT(it, ds) for (it = ds.begin(); it != ds.end(); it++)
#define FUP(i, n) for (i = 0; i < n; i++)

class KeyGen {
public:
  KeyGen();
  string random_new_key();
  string random_old_key();
  void print_old();
  void old_to_new(string s);
  void new_to_old(string s);
  map <string, int> oldmap;
  vector <string> oldvec;
  map <string, int> newmap;
  vector <string> newvec;
};

int seed;

void KeyGen::print_old()
{
  int i;
  printf("# %d %d -", (int) oldvec.size(), (int) oldmap.size());
  VIT(i, oldvec) printf(" %s", oldvec[i].c_str());
  printf("\n");
  fflush(stdout);
}
  
KeyGen::KeyGen()
{
  string s;

  srand48(seed);
    
  while (getline(cin, s)) {
    if (newmap.find(s) != newmap.end()) {
      printf("%s\n", s.c_str());
      exit(1);
    }
    newmap[s] = newvec.size();
    newvec.push_back(s);
  }
}

string KeyGen::random_old_key()
{
  if (oldvec.size() == 0) return "";
  return oldvec[lrand48()%oldvec.size()];
}
  
string KeyGen::random_new_key()
{
  if (newvec.size() == 0) return "";
  return newvec[lrand48()%newvec.size()];
}
  
void KeyGen::old_to_new(string s)
{
  int i, sz, index;
  map <string, int>::iterator oit;
  
/*  printf("# OTN BEFORE: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(), (int) oldvec.size(),
    (int) newmap.size(), (int) newvec.size()); */
  oit = oldmap.find(s);
  if (oit == oldmap.end()) { cerr << "Problems old_to_new\n"; exit(1); }
  newmap[s] = newvec.size();
  newvec.push_back(s);
  sz = oldvec.size()-1;
  index = oit->second;
  oldvec[index] = oldvec[sz];
  oldmap[oldvec[index]] = index;
  oldvec.pop_back();
  oldmap.erase(oit);
/*  printf("# OTN  AFTER: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(),
    (int) oldvec.size(), (int) newmap.size(), (int) newvec.size()); */

  
}

void KeyGen::new_to_old(string s)
{
  int i, sz, index;
  map <string, int>::iterator oit;
  
/*  printf("# NTO BEFORE: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(),
    (int) oldvec.size(), (int) newmap.size(), (int) newvec.size()); */
  oit = newmap.find(s);
  if (oit == newmap.end()) { cerr << "Problems new_to_old\n"; exit(1); }
  oldmap[s] = oldvec.size();
  oldvec.push_back(s);
  sz = newvec.size()-1;
  index = oit->second;
  newvec[index] = newvec[sz];
  newmap[newvec[index]] = index;
  newvec.pop_back();
  newmap.erase(oit);
/*  printf("# NTO  AFTER: %s %d %d %d %d\n", s.c_str(), (int) oldmap.size(),
    (int) oldvec.size(), (int) newmap.size(), (int) newvec.size()); */
}

main(int argc, char **argv)
{
  int e, ne, lp, i, j;
  string s;
  int rn;
  vector <string> to_strip;

  if (argc != 3) { cerr << "usage: rinp nevents seed(-1)\n"; exit(1); }
  ne = atoi(argv[1]);
  seed = atoi(argv[2]);
  if (seed == -1) seed = time(0);
  KeyGen kg;

  lp = -2;

  for (e = 0; e < ne; e++) {
    rn = lrand48()%75;
    if (rn < 25) {
      s = kg.random_new_key();
      if (s == "") {
        e--;
      } else {
        kg.new_to_old(s);
        printf("INSERT %s\n", s.c_str());
      }
    } else if (rn < 30) {
      s = kg.random_old_key();
      if (s == "") {
        e--;
      } else {
        printf("INSERT %s\n", s.c_str());
      }
    } else if (rn < 40) {
      s = kg.random_old_key();
      if (s == "") {
        e--;
      } else {
        printf("PRESENT %s\n", s.c_str());
      }
    } else if (rn < 50) {
      s = kg.random_new_key();
      if (s == "") {
        e--;
      } else {
        printf("PRESENT %s\n", s.c_str());
      }
    } else if (rn < 56) {
      s = kg.random_old_key();
      if (s == "") {
        e--;
      } else {
        printf("ERASE %s\n", s.c_str());
        kg.old_to_new(s);
      }
    } else if (rn < 59) {
      s = kg.random_new_key();
      if (s == "") {
        e--;
      } else {
        printf("ERASE %s\n", s.c_str());
      }
    } else if (rn < 69) {
      s = kg.random_old_key();
      if (s == "" || lrand48()%10 == 0) {
        s = "";
        for (i = 0; i < 3; i++) s.push_back('a' + lrand48()%26);
      } else {
        i = lrand48()%4+1;
        if (i <= s.size()) {
          j = lrand48()%(s.size()-i);
          if (s[j] == ' ') j--;
          s = s.substr(j, i);
          if (s[i-1] == ' ') s.resize(i-1);
        }
      }
      printf("STRIP %s\n", s.c_str());
      to_strip.clear();
      VIT(i, kg.oldvec) {
        if (kg.oldvec[i].find(s) != string::npos) to_strip.push_back(kg.oldvec[i]);
      }
      VIT(i, to_strip) kg.old_to_new(to_strip[i]);
    } else {
      if (lp == e-1) {
        e--;
      } else {
        printf("PRINT\n");
        VIT(i, kg.oldvec) printf("# %s\n", kg.oldvec[i].c_str());
        lp = e;
      }
    }
  }
  if (e-1 != lp) printf("PRINT\n");
  VIT(i, kg.oldvec) printf("# %s\n", kg.oldvec[i].c_str());
}


/*
25 25 INSERT good
30 5 INSERT bad
40 10 PRESENT good
50 10 PRESENT bad
55 5 ERASE good
59 4 ERASE bad
69 10 STRIP
75 6 PRINT
*/
