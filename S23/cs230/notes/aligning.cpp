#include <cstdio>
#include <iostream>
using namespace std;

struct MyStruct {
  char a; 
  int b;
};

extern "C" {
  align_up(long value);
  print_long(long value);
} 

long align_down(long value) {
  return value % -16;
}

int main() {
  long val;

  cout << "Enter a value: ";
  cin >> val;

  cout << "Value aligned to 16 = " << align_up(val) << '\n';
}
