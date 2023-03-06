/* Class notes March 3, 2023 
 * Demonstrates comparison of floating point registers
 *
*/
#include <iostream>
using namespace std;

extern "C" {
  bool compare (float a, double *b);
}

int main() {
  float f;
  double j;
  double *b = 

  cout << "Enter two numbers: ";
  cin >> f >> j;

  if (compare (f, j)) {
    cout << "They are equal!\n";
  }
  else {
    cout << "They are not equal!\n";
  }
}
