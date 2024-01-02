/* Practice C code, read from a file and print the cheapest path to Hogwards */

#include <stdio.h> // new best friends
#include <stdlib.h>

struct Location {
  int Coin;
  int Jumps;
  char Loc[1000];
};

int main(int argc, char **argv) {
  int myCoin, currCoin, jumps;
  char line[100], loc[1000]; // statically cast char
  FILE* filename; // file pointer
  struct Location* n;

  if (argc != 2) { // error check args
    printf("./dobbie filename.txt\n");
    return 0;
  }

  filename = fopen(argv[1], "r"); // try to open file
  if (filename == NULL) { // error check noncompatible files
    printf("File did not open properly\n");
    return 0;
  } 

  while (fgets(line, 100, filename) != NULL) { // read each independent line
    printf("%s", line);
  }
  return 1;
}
