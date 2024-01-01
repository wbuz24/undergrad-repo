/*Practice C code, read names from a file */

#include <stdio.h> // new best friends
#include <stdlib.h>

int main(int argc, char **argv) {
  char line[100]; // statically cast char
  FILE* filename; // file pointer

  if (argc != 2) { // error check args
    printf("./a.out filename.txt\n");
    return 0;
  }

  filename = fopen(argv[1], "r"); // try to open file
  if (filename == NULL) { // error check noncompatible files
    printf("File did not open properly\n");
    return 0;
  } 

  while (fgets(line, 100, filename) != NULL) { // read each independent line
    
    printf("%s", line); // print each line
  }
  return 1;
}
