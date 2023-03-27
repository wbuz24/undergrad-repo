#include "SwappingDigits.cpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
  string arg, number;
  vector <int> x, y;
  SwappingDigits sd;
  int i;
  size_t j;

  if (argc != 2) {
    cerr << "usage: a.out example-number-or-dash\n";
    return 1;
  }

  arg = argv[1];
  if (arg == "-") {
    if (!(cin >> number)) {
      cerr << "No number given\n";
    } else if (number[0] == '0') {
      cerr << "The number starts with zero\n";
    } else if (number.find_first_not_of("0123456789") != string::npos) {
      cerr << "The number has non-digit characters in it.\n";
    }
  } else if (atoi(argv[1]) == 0) {
    number = "596";
  } else if (atoi(argv[1]) == 1) {
    number = "93561";
  } else if (atoi(argv[1]) == 2) {
    number = "5491727514";
  } else if (atoi(argv[1]) == 3) {
    number = "10234";
  } else if (atoi(argv[1]) == 4) {
    number = "93218910471211292416";
  } else {
    cerr << "Bad example number.\n";
    return 1;
  }
  cout << sd.minNumber(number) << endl;
  return 0;
}


