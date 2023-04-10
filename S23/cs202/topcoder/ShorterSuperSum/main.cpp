#include "ShorterSuperSum.cpp"

int main(int argc, char **argv)
{
  int i;
  class ShorterSuperSum TheClass;
  long long retval;
  string a;
  int k, n;

  if (argc != 2) { fprintf(stderr, "usage: a.out num (or - to read from standard input)\n"); exit(1); }


 a = argv[1];
 if (a == "-") {
   if (!(cin >> k >> n)) exit(1);

 } else {

    if (atoi(argv[1]) == 0) {
      k = 1; n = 3;
    }

    if (atoi(argv[1]) == 1) {
      k = 2; n = 3;
    }

    if (atoi(argv[1]) == 2) {
      k = 4; n = 10;
    }

    if (atoi(argv[1]) == 3) {
     k = 10; n = 10;
    }

  }

  retval = TheClass.calculate(k, n);
  cout << retval << endl;

  exit(0);
}
