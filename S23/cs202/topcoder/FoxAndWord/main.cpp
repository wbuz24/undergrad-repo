#include <string.h>
#include "FoxAndWord.cpp"

int main(int argc, char **argv)
{
  int i;
  class FoxAndWord TheClass;
  int retval;
  vector <string> words;
  string s;

  if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

/*
  words = ;
*/

 if (strcmp(argv[1], "-") == 0) {
   while (cin >> s) words.push_back(s);

 } else {

   if (atoi(argv[1]) == 0) {
      words.push_back("tokyo");
      words.push_back("kyoto");
    }
  
   if (atoi(argv[1]) == 1) {
      words.push_back("aaaaa");
      words.push_back("bbbbb");
    }
  
   if (atoi(argv[1]) == 2) {
      words.push_back("ababab");
      words.push_back("bababa");
      words.push_back("aaabbb");
    }
  
   if (atoi(argv[1]) == 3) {
      words.push_back("eel");
      words.push_back("ele");
      words.push_back("lee");
    }
  
   if (atoi(argv[1]) == 4) {
      words.push_back("aaa");
      words.push_back("aab");
      words.push_back("aba");
      words.push_back("abb");
      words.push_back("baa");
      words.push_back("bab");
      words.push_back("bba");
      words.push_back("bbb");
    }
  
   if (atoi(argv[1]) == 5) {
      words.push_back("top");
      words.push_back("coder");
    }
  }

  retval = TheClass.howManyPairs(words);
  cout << retval << endl;

  exit(0);
}
