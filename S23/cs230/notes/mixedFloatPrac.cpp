/* Class notes March 1, 2023
 * Mixing float and double data types
 * Similar to exam question
 * adds two floating point registers
*/

#include <cstdio>

extern "C" {
  double myfunc(double *value, double value2); // (a0, fa0) storing a pointer and double 
}

int main() {
  double a = 10;
  double b = 20;

  double result = myfunc(&a, b); // not actually passing a double, passing a pointer

  printf("%lf\n", result);
}
