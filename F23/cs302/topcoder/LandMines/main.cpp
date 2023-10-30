#include "LandMines.cpp"

int main(int argc, char **argv)
{
  int i;
  string s;
  class LandMines TheClass;
  int retval;
  vector <string> layout;

  if (argc != 2) { fprintf(stderr, "usage: a.out num (or - to read from stdin)\n"); exit(1); }

  if ((string) argv[1] == "-") {
    while (cin >> s) layout.push_back(s);
  } else {

    if (atoi(argv[1]) == 0) {
      layout.push_back("-M-");
      layout.push_back("---");
      layout.push_back("M--");
    }
  
    if (atoi(argv[1]) == 1) {
      layout.push_back("-M-");
      layout.push_back("-M-");
      layout.push_back("--M");
    }
  
    if (atoi(argv[1]) == 2) {
      layout.push_back("--M-");
      layout.push_back("-MM-");
      layout.push_back("----");
      layout.push_back("----");
    }
  
    if (atoi(argv[1]) == 3) {
      layout.push_back("-----");
      layout.push_back("--M-M");
      layout.push_back("-----");
      layout.push_back("-M---");
      layout.push_back("---M-");
    }
  }

  retval = TheClass.numClear(layout);
  cout << retval << endl;

  exit(0);
}
