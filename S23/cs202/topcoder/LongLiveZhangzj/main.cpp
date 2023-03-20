#include "LongLiveZhangzj.cpp"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char **argv)
{
  int i;
  class LongLiveZhangzj TheClass;
  int retval;
  vector <string> speech;
  vector <string> words;
  string s, line;
  istringstream ss;

  if (argc != 2) { fprintf(stderr, "usage: a.out num or - to read the two vectors from standard input (one per line)\n"); exit(1); }

  s = argv[1];
 if (s == "-") {
   if (!getline(cin, line)) return 0;
   ss.str(line);
   while (ss >> s) speech.push_back(s);
   if (!getline(cin, line)) return 0;
   ss.clear();
   ss.str(line);
   while (ss >> s) words.push_back(s);
 } else {

 if (atoi(argv[1]) == 0) {
    speech.push_back("make");
    speech.push_back("topcoder");
    speech.push_back("great");
    speech.push_back("again");
    words.push_back("make");
    words.push_back("america");
    words.push_back("great");
    words.push_back("again");
  }

 if (atoi(argv[1]) == 1) {
    speech.push_back("toads");
    words.push_back("toad");
  }

 if (atoi(argv[1]) == 2) {
    speech.push_back("a");
    speech.push_back("a");
    words.push_back("a");
  }

 if (atoi(argv[1]) == 3) {
    speech.push_back("je");
    speech.push_back("le");
    speech.push_back("ai");
    speech.push_back("deja");
    speech.push_back("vu");
    speech.push_back("et");
    speech.push_back("je");
    speech.push_back("le");
    speech.push_back("veux");
    speech.push_back("encore");
    words.push_back("i");
    words.push_back("am");
    words.push_back("having");
    words.push_back("deja");
    words.push_back("vu");
    words.push_back("please");
    words.push_back("stop");
    words.push_back("the");
    words.push_back("encore");
  }
  }

  retval = TheClass.donate(speech, words);
  cout << retval << endl;

  exit(0);
}
