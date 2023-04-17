#include "AlienAndPassword.cpp"

int main(int argc, char **argv)
{
  int i;
  class AlienAndPassword TheClass;
  int retval;
  string S;

  if (argc != 2) { fprintf(stderr, "usage: a.out num or - for stdin\n"); exit(1); }

  if (strcmp(argv[1], "-") == 0) {
    cin >> S;
  } else {

    if (atoi(argv[1]) == 0) {
       S = "A";
    }
   
    if (atoi(argv[1]) == 1) {
       S = "ABA";
    }
   
    if (atoi(argv[1]) == 2) {
       S = "AABACCCCABAA";
    }
   
    if (atoi(argv[1]) == 3) {
       S = "AGAAGAHHHHFTQLLAPUURQQRRRUFJJSBSZVJZZZ";
    }
   
    if (atoi(argv[1]) == 4) {
       S = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    }
  }

  retval = TheClass.getNumber(S);
  cout << retval << endl;

  exit(0);
}
