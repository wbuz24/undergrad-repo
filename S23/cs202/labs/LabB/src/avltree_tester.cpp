#include "avltree.hpp"
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
using CS202::AVLTree;

void print_commands()
{
  cout << "usage: avltree_tester prompt(- for empty) -- commands on stdin." << endl;
  cout << endl;
  cout << "commands:" << endl;
  cout << "  INSERT name phone ssn  - Insert the person into the tree." << endl;
  cout << "  FIND name              - Find the person and print them out." << endl;
  cout << "  DELETE person          - Delete the person." << endl;
  cout << "  PRINT                  - Print the keys using the Print() method." << endl;
  cout << "  EMPTY                  - Print whether the tree is empty." << endl;
  cout << "  SIZE                   - Print the tree's size." << endl;
  cout << "  HEIGHT                 - Print the tree's height." << endl;
  cout << "  IS_AVL                 - Verifies that the tree is an avl tree." << endl;
  cout << "  KEYS                   - Print the keys using the Ordered_Keys() method." << endl;
  cout << "  VALS                   - Print the vals using the Ordered_Vals() method." << endl;
  cout << "  PRINT_COPY             - Call the copy constructor and call its Print() method." << endl;
  cout << "  ASSIGNMENT             - Test the assignment overload." << endl;
  cout << "  CLEAR                  - Clear the tree back to an empty tree." << endl;
  cout << "  DESTROY                - Call the destructor and remake an empty tree." << endl;
  cout << "  QUIT                   - Quit." << endl;
  cout << "  ?                      - Print commands." << endl;
}

class Person {
  public:
    string name;
    string phone;
    string ssn;
    void Print() const;
};

void Person::Print() const
{
  printf("%-30s %-11s %-11s\n", name.c_str(), phone.c_str(), ssn.c_str());
}

void print_copy(AVLTree t)
{
  t.Print();
}

int main(int argc, char **argv)
{
  string s, line;
  vector <string> sv;
  istringstream ss;
  string prompt;
  Person *p;
  AVLTree *t1, *t2, *tmp;
  vector <void *> vals;
  vector <string> keys;
  size_t i;

  if (argc != 2) { print_commands(); return 1; }
  prompt = argv[1];

  t1 = new AVLTree;
  t2 = new AVLTree;

  while (1) {
 
    /* Print a prompt, and read in a line. */

    if (prompt != "-") {
      cout << prompt << " ";
      cout.flush();
    }
    if (!getline(cin, line)) return 0;

    /* Use a stringstream to turn the line into a vector of words. */

    sv.clear();
    ss.clear();
    ss.str(line);
    while (ss >> s) sv.push_back(s);

    /* Ignore blank lines and lines that start with the pound sign. */

    if (sv.size() == 0 || sv[0][0] == '#') {

    /* With the INSERT command, we create a Person, and then insert it into the tree with
       the name as its key, and a pointer to the person (cast as a (void *)) as its val. */

    } else if (sv[0] == "INSERT") {
      if (sv.size() != 4) {
        cout << "usage: INSERT name phone ssn" << endl;
      } else {
        p = new Person;
        p->name = sv[1];
        p->phone = sv[2];
        p->ssn = sv[3];
        if (!t1->Insert(p->name, (void *) p)) {              /* Here's where we cast to a (void *) */
          cout << "Insert " << p->name << " failed." << endl;
          delete p;
        }
      }

    } else if (sv[0] == "PRINT") {
      t1->Print();

    } else if (sv[0] == "PRINT_COPY") {
      print_copy(*t1);

    } else if (sv[0] == "EMPTY") {
      cout << ((t1->Empty()) ? "Yes" : "No") << endl;

    } else if (sv[0] == "IS_AVL") {
      s = t1->Is_AVL();
      if (s != "") {
        cout << "Not an AVL tree:" << endl << s << endl;
        return 1;
      }

    } else if (sv[0] == "CLEAR") {
      t1->Clear();

    } else if (sv[0] == "SIZE") {
      cout << t1->Size() << endl;

    } else if (sv[0] == "HEIGHT") {
      cout << t1->Height() << endl;

    /* The VALS command calls Ordered_Vals() to get a vector of (void *)'s.
       We typecast each to a (Person *) and then print the person. */

    } else if (sv[0] == "VALS") {
      vals = t1->Ordered_Vals();
      for (i = 0; i < vals.size(); i++) {
        p = (Person *) vals[i];
        p->Print();
      }

    /* I do this so that there may well be a tree in t2 when you make the call. */

    } else if (sv[0] == "ASSIGNMENT") {
      *t2 = *t1;
      tmp = t1;
      t1 = t2;
      t2 = tmp;

    } else if (sv[0] == "DESTROY") {
      delete t1;
      t1 = new AVLTree;

    } else if (sv[0] == "KEYS") {
      keys = t1->Ordered_Keys();
      for (i = 0; i < keys.size(); i++) cout << keys[i] << endl;

    /* Grab the person first, so that there's no memory leak. 
       If the deletion is successful, we'll delete the person. */

    } else if (sv[0] == "DELETE") {
      if (sv.size() != 2) {
        cout << "usage: DELETE key" << endl;
      } else {
        p = (Person *) t1->Find(sv[1]);
        if (t1->Delete(sv[1])) {
          delete p;
        } else {
          cout << "Not found.\n";
        }
      }

    /* The Find() method returns a (void *), so I must typecast it to a (Person *) */

    } else if (sv[0] == "FIND") {
      if (sv.size() != 2) {
        cout << "usage: FIND key" << endl;
      } else {
        p = (Person *) t1->Find(sv[1]);
        if (p == NULL) {
          cout << "Not found.\n";
        } else {
          p->Print();
        }
      }

    } else if (sv[0] == "QUIT") {
      return 0;
    } else if (sv[0] == "?") {
      print_commands();
    } else {
      printf("Unknown command %s\n", sv[0].c_str());
    }
  }
}
