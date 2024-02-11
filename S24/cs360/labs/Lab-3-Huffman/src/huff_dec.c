// Lab 3 
// Will Buziak
// CS360
// Hex dump

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

  fseek(input, 4, SEEK_END);
  last = fgetc(input);
  bytes = (last / 8) + 4;
  
  printf("%u\n\n", bytes);
/*
  while (fgets(line, 100, filename) != NULL) { // read each independent line
    printf("%s", line);
  } */
  return 0;

}
