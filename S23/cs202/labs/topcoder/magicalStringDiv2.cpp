/* Topcoder Problem 02/06/2023
 * Will Buziak
 * cs202
*/
#include <iostream>
#include <cstring>
using namespace std;


class MagicalStringDiv2{
    public:
        int minimalMoves(string s);
};

int MagicalStringDiv2::minimalMoves(string s) {
    int result = 0, n = s.size();
    
    for (int i  = 0; i < n; i++) {
        if (i < (n/2) && s[i] != '>') {
            result++;
        }

        if (i >= (n/2) && s[i] != '<') {
            result++;
        }
    }
    return result;
    
}


int main(int argc, char **argv)
{
  int i;
  class MagicalStringDiv2 TheClass;
  int retval;
  string S;

  if (argc != 2) { fprintf(stderr, "usage: a.out num or - for stdin\n"); exit(1); }

  if (strcmp(argv[1], "-") == 0) {
    cin >> S;
  } else {

    if (atoi(argv[1]) == 0) {
       S = ">><<><";
    }
   
    if (atoi(argv[1]) == 1) {
       S = ">>>><<<<";
    }
   
    if (atoi(argv[1]) == 2) {
       S = "<<>>";
    }
   
    if (atoi(argv[1]) == 3) {
       S = "<><<<>>>>><<>>>>><>><<<>><><><><<><<<<<><<>>><><><";
    }
  }

  retval = TheClass.minimalMoves(S);
  cout << retval << endl;

  exit(0);
}

