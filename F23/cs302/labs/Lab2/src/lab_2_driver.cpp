#include <map>
#include <set>
#include <vector>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <iostream>
#include "lab_2.hpp"
using namespace std;

static uint32_t X[5];
static map <unsigned int, double> waypoints;

uint32_t a502b9de() {
  uint64_t sum;
  sum = (uint64_t)2111111111UL * (uint64_t)X[3] +
     (uint64_t)1492 * (uint64_t)(X[2]) +
     (uint64_t)1776 * (uint64_t)(X[1]) +
     (uint64_t)5115 * (uint64_t)(X[0]) +
     (uint64_t)X[4];
  X[3] = X[2];  X[2] = X[1];  X[1] = X[0];
  X[4] = (uint32_t)(sum >> 32);
  X[0] = (uint32_t)sum;
  return X[0];
}

void de6c340b2(uint32_t c0a61ba) {
  int i;
  uint32_t d709236 = c0a61ba;
  for (i = 0; i < 5; i++) {
    d709236 = d709236 * 29943829 - 1;
    X[i] = d709236;
  }
  for (i=0; i<19; i++) a502b9de();
}

static unsigned long long n;
static double d;

bool am_i_greater_ll(unsigned long long v)
{
  return (v > n);
}

double func(unsigned int x)
{
  map <unsigned int, double>::iterator l, h;
  double dx, dh, dl;

  l = waypoints.lower_bound(x);
  if (l->first == x) return l->second;
  h = l;
  l--;
  dx = x;
  dh = h->first;
  dl = l->first;
  // printf("L:%u,%lg   H:%u,%lg\n", l->first, l->second, h->first, h->second);
  return l->second + (dx - dl) / (dh - dl) * (h->second - l->second);
}

bool am_i_greater_d(double v)
{
  return (v > d);
}

int main() 
{
  int s, i, shift;
  int sel;
  uint32_t *np;
  unsigned long long rv;
  double v;
  double rvd;
  set <long long> x;
  set <long long>::iterator xit;
  vector <double> dy;
  map <unsigned int, double>::iterator wit;
  double max;
  unsigned int maxi, uirv;

  np = (uint32_t *) &n;

  if (cin >> s >> sel) {
    de6c340b2(s);
    if (sel == 0) {
      if (s%20 == 10) {
        n = 0;
      } else if (s%20 == 5) {
        n = 0xffffffffffffffffULL;
      } else {
        np[0] = a502b9de();
        np[1] = a502b9de();
      }
      rv = whats_my_number_ll();
      printf("%llx %llx %s\n", rv, n, (rv == n) ? "Correct" : "Incorrect" );
      
    } else if (sel == 1) {
      if (s%20 == 10) {
        d = 0;
      } else if (s%20 == 5) {
        d = 1000000000.0;
      } else {
        d = (double) a502b9de();
        d /= (double) a502b9de();
        while (d > 1000000000.0) d/= 10.0;
      }
      rvd = whats_my_number_d();
      printf("%.8lf %.8lf %s\n", rvd, d, 
             (rvd-d < 0.000000001 && rvd-d > -0.000000001) ? "Correct" : "Incorrect");
    } else if (sel == 2) {
      x.insert(0);
      x.insert(0xffffffff);
      while (x.size() < 20) x.insert(a502b9de());
      while (dy.size() < 20) {
        d = (double) a502b9de();
        d /= (double) a502b9de();
        while (d > 100000) d /= 2.0;       
        while (d < 100000) d *= 2.0;       
        dy.push_back(d);
      }
      shift = a502b9de()%21;
      for (i = shift; i < 20; i++) dy[i] = -dy[i];
      xit = x.begin();
      v = 0;
      max = 0;
      maxi = 0;
      for (i = 0; i < 20; i++) {
        v += dy[i];
        waypoints[*xit] = v;
        if (i == 0 || v > max) {
          max = v;
          maxi = *xit;
        }
        xit++;
      }

      // for (wit = waypoints.begin(); wit != waypoints.end(); wit++) {
      //   printf("A %u %lf\n", wit->first, wit->second);
      // }
      uirv = optimal();
      printf("%u %u %s\n", uirv, maxi, (uirv == maxi) ? "Correct" : "Incorrect");
    }
  }  
  return 0;
}
