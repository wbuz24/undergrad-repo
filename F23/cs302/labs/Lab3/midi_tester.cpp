#include <cstdlib>
#include "cs302-midi.h"

int main()
{
  CS302_Midi *midi;
  string s, file, format;
  double start, duration, factor;
  
  midi = NULL;

  while (cin >> s) {

    if (s == "READ") {
      if (midi != NULL) delete midi;
      if (!(cin >> file)) {
        cerr << "Incomplete READ\n";
        exit(1);
      }
      midi = new CS302_Midi(file);

    } else if (s == "WRITE") {
      if (!(cin >> format >> file)) {
        cerr << "Incomplete WRITE\n";
        exit(0);
      }
      if (format != "E" && format != "N") {
        cerr << "WRITE -- Format must be E or N\n";
        exit(1);
      }
      if (midi == NULL) {
        cerr << "Can't WRITE an empty file\n";
        exit(1);
      }
      midi->Write(file, format[0]);

    } else if (s == "EXIT") {
      exit(0);

    } else if (s == "ADD_PAUSE") {
      if (!(cin >> start >> duration) || start < 0 || duration < 0) {
        cerr << "ADD_PAUSE -- Should be followed with start and duration\n";
        exit(0);
      }
      if (midi == NULL) {
        cerr << "Can't ADD_PAUSE on an empty file\n";
        exit(1);
      }
      midi->Add_Pause(start, duration);

    } else if (s == "SCALE") {
      if (!(cin >> factor) || factor <= 0) {
        cerr << "SCALE -- Should be followed with a scaling factor\n";
        exit(0);
      }
      if (midi == NULL) {
        cerr << "Can't SCALE on an empty file\n";
        exit(1);
      }
      midi->Scale(factor);

    } else {
      cerr << "Unrecognized command: " << s << endl << endl;
      cerr << "Valid comments: READ WRITE ADD_PAUSE SCALE EXIT\n";
      exit(1);
    }
  }
  return 0;
}
