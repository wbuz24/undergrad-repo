/* Lab 3 
   Will Buziak
   CS360
   Hex dump */

#include <stdio.h>
#include <stdlib.h>

struct huff_node {
  struct huff_node *Zero;
  struct huff_node *One;
  char *S_zero;
  char *S_one;
};

int main(int argc, char **argv) {
  FILE *def, *input; // file pointer
  char *line;
  u_int32_t last, bytes;

  if (argc != 3) { // error check args
    printf("./bin/huff_dec code_definition.txt input.txt\n");
    return 0;
  }

  def = fopen(argv[1], "r"); // try to open file
  input = fopen(argv[2], "r"); // try to open file
  if (def == NULL || input == NULL) { // error check noncompatible files
    printf("File did not open properly\n");
    exit(0);
  } 

  fseek(input, -4, SEEK_END);
  last = fgetc(input);
  bytes = (last / 8) + 4;
  fseek(input, 0, SEEK_SET);

  printf("%u\n\n", bytes);

  if (bytes >= 4) {
    line = (char *) malloc(sizeof(char) * bytes);
    while (fread(line, 1, bytes, input) > 0) { // read each independent line
      printf("%s", line);
    } 
  }
  else printf("Not enough bytes\n");
  return 0;

}
