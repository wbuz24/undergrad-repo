#include "hash_202.hpp"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

void print_commands()
{
  cout << "A key val      Add the given key/val pair to the hash table.\n";
  cout << "F key          Find the given key in the hash table.\n";
  cout << "P              Print the hash table.\n";
  cout << "TP             Print the total probes for finding all keys.\n";
  cout << "Q              Quit.\n";
  cout << "?              Print comands.\n";
}

int main(int argc, char **argv)
{
  string function, collision, key, prompt;
  Hash_202 hash_table;
  size_t table_size;
  string name;
  size_t i;

  string s, line;         // I use these to read a line of text and turn it into a
  vector <string> sv;     // vector of strings (which is in sv).
  istringstream ss;

  try {

    /* Process the command line and error check.  You'll note, I don't error check 
       whether function or collision are correct.  That gets done in hash_tabl.Set_Up(),
       which I call after error checking the arguments. */

    if (argc != 5 && argc != 4) throw((string) "");
    ss.clear(); ss.str(argv[1]); if (!(ss >> table_size)) throw((string) "Bad Table Size");
    function = argv[2];
    collision = argv[3];
    prompt = (argc == 5) ? argv[4] : "";
    if (prompt.size() > 0 && prompt[prompt.size()-1] != ' ') prompt.push_back(' ');

    /* Set up the hash table, and exit on an error. */

    s = hash_table.Set_Up(table_size, function, collision);
    if (s != "") throw(s);

  } catch (string s) {
    cerr << "usage: hash_tester table-size fxn(Last7|XOR) collision(Linear|Double) [prompt]\n";
    if (s != "") cerr << s << endl;
    return 1;
  }

  while (1) {
    cout << prompt;
    cout.flush();

    if(!getline(cin, line)) return 0;
    
    /* Use a stringstream to turn the line into a vector of words. */

    sv.clear();
    ss.clear();
    ss.str(line);
    while (ss >> s) sv.push_back(s);

    /* Ignore blank lines and lines that start with the pound sign. */

    if (sv.size() == 0 || sv[0][0] == '#') {

    /* Handle the commands */

    } else if (sv[0] == "A") {
      if (sv.size() < 3) {
        cout << "usage: A key val(which can be multiple words)\n";
      } else {
        name = sv[2];
        for (i = 3; i < sv.size(); i++) {
          name += " ";
          name += sv[i];
        }
        s = hash_table.Add(sv[1], name);
        if (s != "") {
          cout << "A " << sv[1] << " " << name << endl;
          cout << s << endl;
        }
      }

    } else if (sv[0] == "F") {
      if (sv.size() != 2) {
        cout << "usage: A key\n";
      } else {
        s = hash_table.Find(sv[1]);
        if (s == "") {
          cout << "Not found.\n";
        } else {
          cout << "Found: " << s << endl;
        }
      }

    } else if (sv[0] == "P") {
      hash_table.Print();

    } else if (sv[0] == "TP") {
      cout << hash_table.Total_Probes() << endl;

    /* Quit, print commands or a bad command. */

    } else if (sv[0] == "Q") {
      return 0;
    } else if (sv[0] == "?") {
      print_commands();
    } else {
      printf("Unknown command %s\n", sv[0].c_str());
    }
  }

}
