/* Lab 3 
   Will Buziak
   CS360
   Hex dump */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct huff_node {
  struct huff_node *Zero;
  struct huff_node *One;
  char *S_zero;
  char *S_one;
} Node;

int main(int argc, char **argv) {
  FILE *def, *input; // file pointer
  char *line;
  char c;
  char word[1000], nums[1000];
  int l;
  u_int32_t last, bytes;
  Node *n;

  if (argc != 3) { // error check args
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

  // printf("%u\n\n", bytes);

  if (bytes >= 4) {
    
    n = (Node *) malloc(sizeof(Node));
    n->Zero = NULL;
    n->One = NULL;

    while (fread(&c, 1, 1, def) > 0) {

      l = 0;
      if (c != '\0' && c != '0' && c != '1') {
        /* Find out how long the string is */
        while (c != '\0') {
          word[l] = c;
          fread(&c, 1, 1, def);
          l++;
        }
        word[l] = c;

        printf("%s\n", word);

      }

      if (c == '0') {
        while (n->Zero != NULL) n = n->Zero;
        
//        n->S_zero = strdup(word);
      } 


//      if (c == '\0') printf("\n");
      //printf("%c", c);
    }

    free(n);

   /* line = (char *) malloc(sizeof(char) * bytes);
    while (fread(line, 1, bytes, input) > 0) { // read each independent line
      printf("%s", line);
    }*/ 
  }
  return 1;

}
