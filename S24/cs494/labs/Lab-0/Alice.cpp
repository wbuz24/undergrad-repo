/*
 * Will Buziak
 * January 2024
 * CS494
 * Alice Game
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

long long findMinimumValue(long long a, long long b);

long long isSquare(long long a, long long b) {
  double r;
  r = sqrt((double) (a + b));
  if (fmod(r, 1) == 0) return (long long) r;
  return -1;
}

long long findMinimumValue(long long a, long long b) {
  long long low, h, points, high, r;

  if (a == 2 || b  == 2) return -1;
  if (a == 0) return 0;

  r = isSquare(a, b);

  if (r <= 0) return -1;

  high = r;
  low = 0;
  while (low <= high) {
    h = (low + high)/2; 
    points = r*r - (r - h)*(r - h); 

    // Base Cases
    if (points == a) return h;
    if (a - points < 2*(r - h) && fmod(a - points, 2) == 1) return h + 1;
    if (a - points <=  2*(r - h) && fmod(a - points, 2) == 0) return h + 2;
    if (a - points == (2*(r - h) + 1)) return h + 3;

    if (points > a) high /= 2;
    else {
      low += high/2;
      high -= high/2;
    }
  }

  return h;
}

int main(int argc, char **argv) {
  long long a, b;

  (void) argc;
  sscanf(argv[1], "%lld", &a);
  sscanf(argv[2], "%lld", &b);
  printf("%lld\n", findMinimumValue(a, b));
  return 1;
}
