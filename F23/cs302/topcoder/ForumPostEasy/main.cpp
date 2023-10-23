#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "ForumPostEasy.cpp"
using namespace std;

int main(int argc, char **argv)
{
  int i;
  class ForumPostEasy TheClass;
  string retval, l, s;
  vector <string> exactPostTime;
  vector <string> showPostTime;
  istringstream ss;
  

  if (argc != 2) { 
    fprintf(stderr, "usage: a.out num or -\n"); 
    fprintf(stderr, "       if -, then enter all times on the first line, and all show-post-times\n");
    fprintf(stderr, "       on the second line, with dashes instead of spaces.\n");
    exit(1);
  }

  if ((string) argv[1] == "-") {
    if (!getline(cin, l)) return 1;
    ss.clear();
    ss.str(l);
    while (ss >> s) exactPostTime.push_back(s);
    if (!getline(cin, l)) return 1;
    ss.clear();
    ss.str(l);
    while (ss >> s) {
      for (i = 0; i < s.size(); i++) if (s[i] == '-') s[i] = ' ';
      showPostTime.push_back(s);
    }
  } else {

    if (atoi(argv[1]) == 0) {
      exactPostTime.push_back("12:12:12");
      showPostTime.push_back("few seconds ago");
    }
  
    if (atoi(argv[1]) == 1) {
      exactPostTime.push_back("23:23:23");
      exactPostTime.push_back("23:23:23");
      showPostTime.push_back("59 minutes ago");
      showPostTime.push_back("59 minutes ago");
    }
  
    if (atoi(argv[1]) == 2) {
      exactPostTime.push_back("00:10:10");
      exactPostTime.push_back("00:10:10");
      showPostTime.push_back("59 minutes ago");
      showPostTime.push_back("1 hours ago");
    }
  
    if (atoi(argv[1]) == 3) {
      exactPostTime.push_back("11:59:13");
      exactPostTime.push_back("11:13:23");
      exactPostTime.push_back("12:25:15");
      showPostTime.push_back("few seconds ago");
      showPostTime.push_back("46 minutes ago");
      showPostTime.push_back("23 hours ago");
    }
  }

  retval = TheClass.getCurrentTime(exactPostTime, showPostTime);
  cout << retval << endl;

  exit(0);
}

