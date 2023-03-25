#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "fraction.hpp"
using namespace std;


void print_commands()
{
  cout << "QUIT           -- Quit the program.\n";
  cout << "?              -- Print commands.\n";
  cout << "CLEAR          -- Clear the fraction back to one.\n";
  cout << "CALCULATE      -- Calculate the fraction.\n";
  cout << "INVERT         -- Swap the numerator and denominator.\n";
  cout << "PRINT          -- Print the fraction as an equation.\n";
  cout << "MULTIPLY n     -- Multiply the fraction by n.\n";
  cout << "DIVIDE n       -- Divide the fraction by n.\n";
  cout << "MULT_FACT n    -- Multiply the fraction by n!\n";
  cout << "DIV_FACT n     -- Divide the fraction by n!\n";
  cout << "MULT_BINOM n k -- Multiply the fraction by n choose k.\n";
  cout << "DIV_BINOM n k  -- Divide the fraction by n choose k.\n";
  return;
}

int main(int argc, char **argv)
{
  Fraction p;
  string s, line;
  istringstream ss;
  vector <string> sv;
  string prompt;

  if (argc > 2) {
    cerr << "usage: fraction_tester [prompt]\n";
    return 0;
  }
  if (argc == 2) {
    prompt = argv[1];
    prompt.push_back(' ');
  }
  
  while (1) {
    if (prompt != "") {
      cout << prompt;
      cout.flush();
    }
    if (!getline(cin, line)) return 0;
    ss.clear();
    sv.clear();
    ss.str(line);
    while (ss >> s) sv.push_back(s);

    if (sv.size() == 0 || sv[0][0] == '#') {
      // Skip
    } else if (sv[0] == "QUIT") {
      return 0;
    } else if (sv[0] == "?") {
      print_commands();
    } else if (sv[0] ==  "CLEAR") {
      p.Clear();
    } else if (sv[0] ==  "CALCULATE") {
      cout << p.Calculate_Product() << endl;
    } else if (sv[0] ==  "INVERT") {
      p.Invert();
    } else if (sv[0] ==  "PRINT") {
      p.Print();
    } else if (sv[0] ==  "MULTIPLY") {
      if (sv.size() < 2) {
        cout << "usage: MULTIPLY number\n";
      } else if (!p.Multiply_Number(atoi(sv[1].c_str())))  {
        cout << "Failed" << endl;
      }
    } else if (sv[0] ==  "DIVIDE") {
      if (sv.size() < 2) {
        cout << "usage: DIVIDE number\n";
      } else if (!p.Divide_Number(atoi(sv[1].c_str()))) {
        cout << "Failed" << endl;
      }
    } else if (sv[0] ==  "MULT_FACT") {
      if (sv.size() < 2) {
        cout << "usage: MULT_FACT number\n";
      } else if (!p.Multiply_Factorial(atoi(sv[1].c_str()))) {
        cout << "Failed" << endl;
      }
    } else if (sv[0] ==  "DIV_FACT") {
      if (sv.size() < 2) {
        cout << "usage: DIV_FACT number\n";
      } else if (!p.Divide_Factorial(atoi(sv[1].c_str()))) {
        cout << "Failed" << endl;
      }
    } else if (sv[0] ==  "MULT_BINOM") {
      if (sv.size() < 3) {
        cout << "usage: MULT_BINOM n k\n";
      } else if (!p.Multiply_Binom(atoi(sv[1].c_str()), atoi(sv[2].c_str()))) {
        cout << "Failed" << endl;
      }
    } else if (sv[0] ==  "DIV_BINOM") {
      if (sv.size() < 3) {
        cout << "usage: DIV_BINOM n k\n";
      } else if (!p.Divide_Binom(atoi(sv[1].c_str()), atoi(sv[2].c_str()))) {
        cout << "Failed" << endl;
      }
    } else {
      cout << "Bad command.\n";
    }
  }
}
