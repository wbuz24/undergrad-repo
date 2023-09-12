#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
  string s;
  int t, pitch, volume;
  ofstream fout;

  if (argc != 2) {
    cerr << "usage: mef2jmid outputfile < inputfile\n";
    exit(1);
  }

  fout.open(argv[1]);
  if (fout.fail()) {
     cerr << "Couldn't open " << argv[1] << endl;
     exit(1);
  }
  cin >> s;
  if (cin.fail() || s != "CS302-Midi-Event-File") {
        fout.flush();
    cerr << "mef2jmid error: First word is not CS302-Midi-Event-File\n";
    exit(1);
  }

  fout << "JMID FILE\n";
  fout << "Format: 1  ntracks: 1  Division: 240\n";
  fout << "TRACK 0\n";

  while (cin >> s) {
    if (s == "ON") {
      cin >> t;
      if (cin.fail() || t < 0) {
        fout.flush();
        cerr << "mef2jmid error: ON event -- bad time\n";
        exit(1);
      }
      cin >> pitch;
      if (cin.fail() || pitch < 0 || pitch > 128) {
        fout.flush();
        cerr << "mef2jmid error: ON event -- bad pitch\n";
        exit(1);
      }
      cin >> volume;
      if (cin.fail() || volume <= 0 || volume > 128) {
        fout.flush();
        cerr << "mef2jmid error: ON event -- bad volume\n";
        exit(1);
      }
      fout << "    " << t << " NOTE-ON 90 " << pitch << " " << volume << endl;
    } else if (s == "OFF") {
      cin >> t;
      if (cin.fail() || t < 0) {
        fout.flush();
        cerr << "mef2jmid error: OFF event -- bad time\n";
        exit(1);
      }
      cin >> pitch;
      if (cin.fail() || pitch < 0 || pitch > 128) {
        fout.flush();
        cerr << "mef2jmid error: OFF event -- bad pitch\n";
        exit(1);
      }
      fout << "    " << t << " NOTE-OFF 80 " << pitch << endl;
    } else if (s == "DAMPER") {
      cin >> t;
      if (cin.fail() || t < 0) {
        fout.flush();
        cerr << "mef2jmid error: DAMPER event -- bad time\n";
        exit(1);
      }
      cin >> s;
      if (cin.fail() || (s != "DOWN" && s != "UP")) {
        fout.flush();
        cerr << "mef2jmid error: DAMPER event -- bad DOWN|UP\n";
        exit(1);
      }
      fout << "    " << t << " CONTROL B0 64 " << ((s == "DOWN") ? "127" : "0" )<< endl;
    } else {
        fout.flush();
      cerr << "mef2jmid error: Unknown KEY: " << s << "\n";
      exit(1);
    }
  }

  fout << "    1000 META       FF 2F 0\n";
}
