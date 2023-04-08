#include "dlist.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
using namespace std;

void Print_Copy(Dlist l)
{
  Dnode *n;

  for (n = l.Begin(); n != l.End(); n = n->Next()) {
    if (n != l.Begin()) cout << " ";
    cout << n->s;
  }
  cout << endl;
}

void print_commands()
{
  cout << "CLEAR:               This calls the Clear() method, clearing the list.\n";
  cout << "DESTROY:             This deletes the list and creates a new one with new.\n";
  cout << "PRINT_FORWARD:       This prints the list, all on one line in the forward direction.\n";
  cout << "PRINT_REVERSE:       This prints the list, all on one line in the reverse direction.\n";
  cout << "PRINT_COPY:          This prints the list using a procedure which calls the copy constructor.\n";
  cout << "PUSH_BACK s:         This calls Push_Back on the string s.\n";
  cout << "PUSH_FRONT s:        This calls Push_Front on the string s.\n";
  cout << "POP_BACK: :          This calls Pop_Back and prints the string\n";
  cout << "POP_FRONT:           This calls Pop_Front and prints the string.\n";
  cout << "ERASE s:             This calls Erase on the pointer to the node that holds string s. \n";
  cout << "                     If s is not on the list, this does nothing.\n";
  cout << "INSERT_BEFORE s1 s2: This calls Insert_Before(s1, d), \n";
  cout << "                     where d is the pointer to the node that holds string s2. \n";
  cout << "                     If s2 is not on the list, this does nothing.\n";
  cout << "INSERT_AFTER s1 s2:  This calls Insert_After(s1, d).\n";
  cout << "EMPTY:               This returns whether the list is empty.\n";
  cout << "SIZE:                This returns the list's size.\n";
  cout << "AO:                  This tests the assignment overload by copying to a second list,\n";
  cout << "                     and then copying back.\n";
  cout << "?:                   Print these commands.\n";
  cout << "QUIT:                Exit.\n";
}

int main(int argc, char **argv)
{
  map <string, Dnode *> words;
  istringstream ss;
  Dlist *l, l2;
  Dnode *n;
  vector <string> sv;
  string s;
  string p;
  string w;

  if (argc != 2) {
    cerr << "usage: dlist_editor prompt(- for none)\n";
    exit(1);
  }

  l = new Dlist;
  p = argv[1];

  while(1) {
    if (p != "-") {
      printf("%s ", p.c_str());
      fflush(stdout);
    }
    if (!getline(cin, s)) exit(0);
    sv.clear();
    ss.clear();
    ss.str(s);
    while (ss >> w) sv.push_back(w);

    if (sv.size() == 0 || sv[0][0] == '#') {
    } else if (sv[0] == "?") {
      print_commands();
    } else if (sv[0] == "DESTROY") {
      if (sv.size() != 1) {
        printf("DESTROY takes no arguments.\n");
      } else {
        delete l;
        words.clear();
        l = new Dlist;
      }
    } else if (sv[0] == "CLEAR") {
      if (sv.size() != 1) {
        printf("CLEAR takes no arguments.\n");
      } else {
        l->Clear();
        words.clear();
      }
    } else if (sv[0] == "EMPTY") {
      if (sv.size() != 1) {
        printf("EMPTY takes no arguments.\n");
      } else {
        cout << ((l->Empty()) ? "Yes" : "No") << endl;
      }
    } else if (sv[0] == "SIZE") {
      if (sv.size() != 1) {
        printf("SIZE takes no arguments.\n");
      } else {
        cout << l->Size() << endl;
      }
    } else if (sv[0] == "ERASE") {
      if (sv.size() != 2) {
        printf("ERASE word.\n");
      } else {
        if (words.find(sv[1]) == words.end()) {
          cout << sv[1] << " is not on the list\n";
        } else {
          l->Erase(words[sv[1]]); 
          words.erase(words.find(sv[1]));
        }
      }
    } else if (sv[0] == "INSERT_BEFORE") {
      if (sv.size() != 3) {
        printf("INSERT_BEFORE s1 s2.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else if (words.find(sv[2]) == words.end()) {
          cout << sv[2] << " is not on the list\n";
        } else {
          n = words[sv[2]];
          l->Insert_Before(sv[1], n);
          words[sv[1]] = n->Prev();
        }
      }
    } else if (sv[0] == "INSERT_AFTER") {
      if (sv.size() != 3) {
        printf("INSERT_AFTER s1 s2.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else if (words.find(sv[2]) == words.end()) {
          cout << sv[2] << " is not on the list\n";
        } else {
          n = words[sv[2]];
          l->Insert_After(sv[1], n);
          words[sv[1]] = n->Next();
        }
      }
    } else if (sv[0] == "PUSH_BACK") {
      if (sv.size() != 2) {
        printf("PUSH_BACK word.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else {
          l->Push_Back(sv[1]);
          words[sv[1]] = l->Rbegin();
        }
      }
    } else if (sv[0] == "PUSH_FRONT") {
      if (sv.size() != 2) {
        printf("PUSH_FRONT word.\n");
      } else {
        if (words.find(sv[1]) != words.end()) {
          cout << sv[1] << " is already on the list\n";
        } else {
          l->Push_Front(sv[1]);
          words[sv[1]] = l->Begin();
        }
      }
    } else if (sv[0] == "POP_FRONT") {
      if (sv.size() != 1) {
        printf("POP_FRONT takes no arguments.\n");
      } else if (l->Empty()) {
        printf("POP_FRONT called on an empty list.\n");
      } else {
        s = l->Pop_Front();
        words.erase(words.find(s));
        cout << s << endl;
      }
    } else if (sv[0] == "POP_BACK") {
      if (sv.size() != 1) {
        printf("POP_BACK takes no arguments.\n");
      } else if (l->Empty()) {
        printf("POP_BACK called on an empty list.\n");
      } else {
        s = l->Pop_Back();
        words.erase(words.find(s));
        cout << s << endl;
      }
    } else if (sv[0] == "PRINT_FORWARD") {
      if (sv.size() != 1) {
        printf("PRINT_FORWARD takes no arguments.\n");
      } else {
        for (n = l->Begin(); n != l->End(); n = n->Next()) {
          if (n != l->Begin()) cout << " ";
          cout << n->s;
        }
        cout << endl;
      }
    } else if (sv[0] == "AO") {
      if (sv.size() != 1) {
        printf("AO takes no arguments.\n");
      } else {
        l2 = *l;
        delete l;
        words.clear();
        l = new Dlist;
        *l = l2;
        for (n = l->Begin(); n != l->End(); n = n->Next()) {
          words[n->s] = n;
        }
      }
    } else if (sv[0] == "PRINT_COPY") {
      if (sv.size() != 1) {
        printf("PRINT_COPY takes no arguments.\n");
      } else {
        Print_Copy(*l);
      }
    } else if (sv[0] == "QUIT") {
      exit(0);
    } else if (sv[0] == "PRINT_REVERSE") {
      if (sv.size() != 1) {
        printf("PRINT_REVERSE takes no arguments.\n");
      } else {
        for (n = l->Rbegin(); n != l->Rend(); n = n->Prev()) {
          if (n != l->Rbegin()) cout << " ";
          cout << n->s;
        }
        cout << endl;
      }
    } else {
      printf("Bad command\n");
    }
  }
  
}
