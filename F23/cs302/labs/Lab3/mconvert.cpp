#include <cstdlib>
#include <cstring>
#include "cs302-midi.h"

int main(int argc, char **argv)
{
  CS302_Midi *midi;

  if (argc != 4 || strlen(argv[3]) != 1 || strchr("EN", argv[3][0]) == NULL) {
    cerr << "usage: mconvert inputfile outputfile format(E|N)\n";
    exit(1);
  }

  midi = new CS302_Midi(argv[1]);
  midi->Write(argv[2], argv[3][0]);
  delete midi;
  return 0;
}
