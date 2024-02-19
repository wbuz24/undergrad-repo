#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  double d;

  d = 12345.6789;
  first();
  second();
  third();
  fourth();
  fifth();
  printf("The log base 10 of %.4lf is %.4lf\n", d, log10(d));

  return 0;
}
