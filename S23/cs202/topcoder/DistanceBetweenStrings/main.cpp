#include "DistanceBetweenStrings.cpp"

int main(int argc, char **argv)
{
  int i;
  class DistanceBetweenStrings TheClass;
  int retval;
  string arg;
  string a;
  string b;
  string letterSet;

  if (argc != 2) { fprintf(stderr, "usage: a.out num (or - to enter input on stdin)\n"); exit(1); }

  arg = argv[1];
  if (arg == "-") {
    if (cin >> a >> b >> letterSet) {
    } else {
      fprintf(stderr, "You need to enter a, b and letterSet on standard input\n");
      exit(1);
    }
  } else {
  
   if (atoi(argv[1]) == 0) {
      a = "topcoder";
      b = "contest";
      letterSet = "tcp";
    }
  
   if (atoi(argv[1]) == 1) {
      a = "abcdef";
      b = "fedcba";
      letterSet = "fed";
    }
  
   if (atoi(argv[1]) == 2) {
      a = "aaaaa";
      b = "bbbbb";
      letterSet = "a";
    }
  
   if (atoi(argv[1]) == 3) {
      a = "aaAaB";
      b = "BbaAa";
      letterSet = "ab";
    }
  
   if (atoi(argv[1]) == 4) {
      a = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
      b = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
      letterSet = "ba";
    }
  
   if (atoi(argv[1]) == 5) {
      a = "ToPcOdEr";
      b = "tOpCoDeR";
      letterSet = "wxyz";
    }
  }

  retval = TheClass.getDistance(a, b, letterSet);
  cout << retval << endl;

  exit(0);
}
