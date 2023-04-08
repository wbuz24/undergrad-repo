#include <string.h>
#include "DivideByZero.cpp"

int main(int argc, char **argv)
{
  int i;
  class DivideByZero TheClass;
  int retval;
  vector <int> words;
  string s;

   if (argc != 2) { fprintf(stderr, "usage: a.out num or -\n"); exit(1); }

/*
  words = ;
*/

  if (strcmp(argv[1], "-") == 0) {
   while (cin >> i) words.push_back(i);

 } else {

    if (atoi(argv[1]) == 0) {
      words.push_back(9);
      words.push_back(2);
    }
  
    if (atoi(argv[1]) == 1) {
      words.push_back(8);
      words.push_back(2);
    }
  
    if (atoi(argv[1]) == 2) {
      words.push_back(50);
    }
  
    if (atoi(argv[1]) == 3) {
      words.push_back(1);
      words.push_back(5);
      words.push_back(8);
      words.push_back(30);
      words.push_back(15);
      words.push_back(4);
    }
  
    if (atoi(argv[1]) == 4) {
      words.push_back(1);
      words.push_back(2);
      words.push_back(4);
      words.push_back(8);
      words.push_back(16);
      words.push_back(32);
      words.push_back(64);
    }
  
    if (atoi(argv[1]) == 5) {
      words.push_back(6);
      words.push_back(2);
      words.push_back(18);
    }
  }

  retval = TheClass.CountNumbers(words);
  cout << retval << endl;

  exit(0);
}

