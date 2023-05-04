#include "TreesAndBrackets.cpp"

int main(int argc, char **argv)
{
  int i;
  class TreesAndBrackets TheClass;
  string retval;
  string t1;
  string t2;
  string a;

  if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

  a = argv[1];

  if (a == "-") {
    if (!(cin >> t1 >> t2)) return 1;

  } else {
    if (atoi(argv[1]) == 0) {
      t1 = "(())";
      t2 = "()";
    }
  
    if (atoi(argv[1]) == 1) {
      t1 = "()";
      t2 = "()";
    }
  
    if (atoi(argv[1]) == 2) {
      t1 = "(()()())";
      t2 = "((()))";
    }
  
    if (atoi(argv[1]) == 3) {
      t1 = "((())((())())())";
      t2 = "(()(())())";
    }
  
    if (atoi(argv[1]) == 4) {
      t1 = "((())((())())())";
      t2 = "((()()()()()))";
    }
  
    if (atoi(argv[1]) == 5) {
      t1 = "(()((()()))(()(()))((()()))()(()(()())(()))())";
      t2 = "((())((()()))(()))";
    }
  
    if (atoi(argv[1]) == 6) {
      t1 = "(((())((())())())((())((())())())((())((())())())((())((())())())((())((())())())((())((())())())())";
      t2 = "((()()()()()))";
    }
  
    if (atoi(argv[1]) == 7) {
      t1 = "((()(()()((()()(()(()((()(((()(())())()())()())())()())())()))()()))()))"; 
      t2 = "(((()(((((((()()())())())())()))))))";
    }
  }
  retval = TheClass.check(t1, t2);
  cout << retval << endl;
  

  exit(0);
}
