#include <map>
#include <set>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include "code_processor.hpp"
using namespace std;
    
void Code_Processor::Double_Check_Internals() const
{
  int fd;
  size_t npn;
  User *u;
  unordered_map <string, User *>::const_iterator uit, u2;
  set <string>::const_iterator pit;
  string p;

  npn = 0;
  for (uit = Names.begin(); uit != Names.end(); uit++) {
    u = uit->second;
    for (pit = u->phone_numbers.begin(); pit != u->phone_numbers.end(); pit++) {
      npn++;
      p = *pit;
      u2 = Phones.find(p);
      if (u2 == Phones.end()) {
        cerr << "Error -- phone " << *pit << " from user " << u->username << " is not in Phones.\n";
        exit(1);
      }
      if (u2->second != u) {
        cerr << "Error -- phone " << *pit << " is not registered to user " << u->username << ".\n";
        exit(1);
      }
    }
  }
  if (npn != Phones.size()) {
    cerr << "Phones.size() does not match the number of user phones.\n";
    exit(1);
  }
  fd = open("/dev/null", O_RDONLY);
  if (fd > 4) {
    cerr << "You have too many files open.\n"; 
    exit(1);
  }
  close(fd);
}
