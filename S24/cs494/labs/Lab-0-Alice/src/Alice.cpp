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
  /* calls sqrt() which is not entirely trustworthy for long long */
  r = sqrt((double) (a + b));
  if (fmod(r, 1) == 0) return (long long) r;
  return -1;
}

long long findMinimumValue(long long a, long long b) {
  long long low, h, points, high, r;

  if (a == 2 || b  == 2) return -1;
  if (a == 0) return 0;

  /* Find if args are a perfect square */
  r = isSquare(a, b);

  if (r <= 0) return -1;
  if (a < 2*r && a % 2 == 1) return 1;
  if (a <= 2*r && a % 2 == 0) return 2;
  if (a == (2*r + 1)) return 3;

  high = r;
  low = 0;
  while (low <= high) {
    h = (low + high)/2; 
    points = r*r - (r-h)*(r-h); // Alice's points for winning h rounds

    /* Alice's points cannot be higher than Alice's score */
    if (points > a) high = h - 1;
    else {
    /* Base Cases */
      if (points == a) return points;
      if (a - points < 2*(r - h) && (a - points) % 2 == 1) return (h + 1);
      if (a - points <=  2*(r - h) && (a - points) % 2 == 0) return (h + 2);
      if (a - points == (2*(r - h) + 1)) return (h + 3);

      /* bottom half */
      low = h + 1;
    }
  }

  return h;
}

int main(int argc, char **argv) {
  long long a, b;

  /* Read in args and call findMinimumValue function */
  (void) argc;
  sscanf(argv[1], "%lld", &a);
  sscanf(argv[2], "%lld", &b);
  printf("%lld\n", findMinimumValue(a, b));
  return 1;
}
