#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

void print_commands()
{
  cout << "usage: pgm_editor [prompt] - commands on standard input\n";
  cout << "\n";
  cout << "        READ filename             - Read the PGM file\n";
  cout << "        WRITE filename            - Write the stored PGM to the file\n";
  cout << "        CREATE rows cols pixvalue - Call Create()\n";
  cout << "        CW                        - Call Clockwise()\n";
  cout << "        CCW                       - Call Cclockwise()\n";
  cout << "        PAD pixels pixvalue       - Call Pad()\n";
  cout << "        PANEL r c                 - Call Panel()\n";
  cout << "        CROP r c rows cols        - Call Crop()\n";
  cout << "        Q                         - Quit\n";
  cout << "        ?                         - Print commands\n";
}

int main(int argc, char **argv)
{
  istringstream ss;
  vector <string> sv;
  string prompt, s, line;
  size_t r, c, rows, cols, pv, w;
  Pgm pgm;

  if (argc > 2) print_commands();
  if (argc == 2) {
    prompt = argv[1];
    prompt += " ";
  }

  while (1) {

    /* Print a prompt, and read in a line. */

    cout << prompt;
    cout.flush();
    if (!getline(cin, line)) return 0;

    /* Use a stringstream to turn the line into a vector of words. */

    sv.clear();
    ss.clear();
    ss.str(line);
    while (ss >> s) sv.push_back(s);

    /* Ignore blank lines and lines that start with the pound sign. */

    try {
      if (sv.size() == 0 || sv[0][0] == '#') {
  
      } else if (sv[0] == "READ") {
        if (sv.size() != 2) throw((string) "usage: READ filename");
        if (!pgm.Read(sv[1])) throw((string) "READ failed");
     
      } else if (sv[0] == "WRITE") {
        if (sv.size() != 2) throw((string) "usage: WRITE filename");
        if (!pgm.Write(sv[1])) throw((string) "WRITE failed");
     
      } else if (sv[0] == "CREATE") {
        if (sv.size() != 4) throw((string) "usage: CREATE rows cols pixelvalue");
        ss.clear(); ss.str(sv[1]); if (!(ss >> r)) throw((string) "Bad rows");
        ss.clear(); ss.str(sv[2]); if (!(ss >> c)) throw((string) "Bad cols");
        ss.clear(); ss.str(sv[3]); if (!(ss >> pv)) throw((string) "Bad pixelvalue");
        if (!pgm.Create(r, c, pv)) throw((string) "CREATE failed");
     
      } else if (sv[0] == "CW") {
        if (!pgm.Clockwise()) throw((string) "CW failed");
     
      } else if (sv[0] == "CCW") {
        if (!pgm.Cclockwise()) throw((string) "CCW failed");
     
      } else if (sv[0] == "PAD") {
        if (sv.size() != 3) throw((string) "usage: PAD w pixelvalue");
        ss.clear(); ss.str(sv[1]); if (!(ss >> w)) throw((string) "Bad w");
        ss.clear(); ss.str(sv[2]); if (!(ss >> pv)) throw((string) "Bad pixelvalue");
        if (!pgm.Pad(w, pv)) throw((string) "PAD failed");
     
      } else if (sv[0] == "PANEL") {
        if (sv.size() != 3) throw((string) "usage: PANEL r c");
        ss.clear(); ss.str(sv[1]); if (!(ss >> r)) throw((string) "Bad rows");
        ss.clear(); ss.str(sv[2]); if (!(ss >> c)) throw((string) "Bad cols");
        if (!pgm.Panel(r, c)) throw((string) "PANEL failed");
     
      } else if (sv[0] == "CROP") {
        if (sv.size() != 5) throw((string) "usage: CROP r c rows cols");
        ss.clear(); ss.str(sv[1]); if (!(ss >> r)) throw((string) "Bad r");
        ss.clear(); ss.str(sv[2]); if (!(ss >> c)) throw((string) "Bad c");
        ss.clear(); ss.str(sv[3]); if (!(ss >> rows)) throw((string) "Bad rows");
        ss.clear(); ss.str(sv[4]); if (!(ss >> cols)) throw((string) "Bad cols");
        if (!pgm.Crop(r, c, rows, cols)) throw((string) "CROP failed");
     
      /* Quit, print commands or a bad command. */

      } else if (sv[0] == "Q") {
        return 0;
      } else if (sv[0] == "?") {
        print_commands();
      } else {
        printf("Unknown command %s\n", sv[0].c_str());
      }
    } catch (const string estring) {
      printf("%s\n", estring.c_str());
    }
  }
}
