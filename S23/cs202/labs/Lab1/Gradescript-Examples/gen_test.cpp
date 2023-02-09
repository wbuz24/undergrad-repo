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

void space()
{
  int i;

  i = lrand48()%10;

  if (i == 0) { printf("\n"); return; }
  if (i < 5) { printf("%*s", i, " "); return; }
  if (i == 6) { printf("\t"); return; }
  if (i == 7) { printf("\n\n"); return; }
  printf(" ");
  return;
}

void random_word()
{
  int i;
  string s;
  space(); 

  i = lrand48()%4;
  if (i == 0) {
    i = lrand48()%4;
    printf("Starrlite");
    while(i > 0) { printf("!"); i--; }
  } else {
    cin >> s;
    printf("%s", s.c_str());
  }
}

main(int argc, char **argv)
{
  int nevents, e, name_before;
  string n;
  double qw;
  int i, j;


  if (argc != 3) {
    fprintf(stderr, "usage: gen_test seed nevents\n");
    exit(1);
  }

  srand48(atoi(argv[1]));
  nevents = atoi(argv[2]);
  name_before = lrand48()%(nevents+1);
  qw = 120.0 / (double) nevents;

  for (e = 0; e < nevents; e++) {
    if (name_before == e) { space(); printf("NAME"); space();
      cin >> n;
      printf("%s", n.c_str());
    }
    if (lrand48()%2) {
      i = lrand48()%4;
      space();
      printf("%.*lf", i, drand48()*qw);
    } else {
      space();
      printf("AVERAGE");
      i = lrand48()%6;
      if (i == 6) i = lrand48()%20+10;
      while (i > 0) {
        space();
        j = lrand48()%4;
        printf("%.*lf", j, drand48()*qw*2);
        i--;
      }
      random_word();
    }
    i = lrand48()%5;
    while (i > 0) {
      random_word();
      i--;
    }
  }
  if (name_before == e) { space(); printf("NAME"); space(); 
    cin >> n;
    printf("%s", n.c_str());
  }

  printf("\n");
}   
