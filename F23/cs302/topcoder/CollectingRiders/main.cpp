#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "CollectingRiders.cpp"

int main(int argc, char **argv)
{
  int i;
  class CollectingRiders TheClass;
  int retval;
  vector <string> board;
  string s;

  if (argc != 2) { fprintf(stderr, "usage: a.out num (or -) \n"); exit(1); }

  if ((string) argv[1] == "-") {
    while (cin >> s) board.push_back(s);
  } else {
    if (atoi(argv[1]) == 0) {
      board.push_back("...1");
      board.push_back("....");
      board.push_back("2...");
    }
  
    if (atoi(argv[1]) == 1) {
      board.push_back("........");
      board.push_back(".1......");
      board.push_back("........");
      board.push_back("....3...");
      board.push_back("........");
      board.push_back("........");
      board.push_back(".7......");
      board.push_back("........");
    }
  
    if (atoi(argv[1]) == 2) {
      board.push_back("..");
      board.push_back("2.");
      board.push_back("..");
    }
  
    if (atoi(argv[1]) == 3) {
      board.push_back(".1....1.");
    }
  
    if (atoi(argv[1]) == 4) {
      board.push_back("9133632343");
      board.push_back("5286698232");
      board.push_back("8329333369");
      board.push_back("5425579782");
      board.push_back("4465864375");
      board.push_back("8192124686");
      board.push_back("3191624314");
      board.push_back("5198496853");
      board.push_back("1638163997");
      board.push_back("6457337215");
    }
  }

  retval = TheClass.minimalMoves(board);
  cout << retval << endl;

  exit(0);
}

