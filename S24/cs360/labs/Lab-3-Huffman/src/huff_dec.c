/* Lab 3 
   Will Buziak
   CS360
   Hex dump */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct huff_node {
  struct huff_node *Ptrs[2];
  char *Strings[2];
} Node;

int main(int argc, char **argv) {
  FILE *def, *input; // file pointer
  char *line;
  char c;
  char word[1000], nums[1000];
  int l;
  u_int32_t last, bytes;
  Node *n, *p, *prev;

  /* Check args */
  if (argc != 3) {
    return 0;
  }

  /* Try to open the two input files for reading */
  def = fopen(argv[1], "r");
  input = fopen(argv[2], "r");

  /* error check files opening */
  if (def == NULL || input == NULL) {
    printf("File did not open properly\n");
    exit(0);
  } 

  fseek(input, -4, SEEK_END);
  last = fgetc(input);
  bytes = (last / 8) + 4;
  fseek(input, 0, SEEK_SET);

  // printf("%u\n\n", bytes);

  if (bytes >= 4) {
    
    /* Create the bottom node in the tree, n */
    n = (Node *) malloc(sizeof(Node));
    n->Ptrs[0] = NULL;
    n->Ptrs[1] = NULL;

    /* p is the node being processed */
    p = n;

  while (fread(&c, 1, 1, def) > 0) {

      l = 0;
      if (c != '\0' && c != '0' && c != '1') {
        /* Insert the string into word */
        while (c != '\0') {
          word[l] = c;
          fread(&c, 1, 1, def);
          l++;
        }
        word[l] = '\0';
      }

      /* Character is 0 or 1 */
      if (c == '0') {
        l = 0;
        /* Insert the number into a string */
        while (c != '\0') {
          nums[l] = c;
          l++;
          fread(&c, 1, 1, def);
        }
        nums[l] = '\0';
        while (p->Ptrs[0] != NULL) p = p->Ptrs[0];

        /* Store the string and create a new node */
        p->Strings[0] = strdup(word);
        prev = p;
        
        p = (Node *) malloc(sizeof(Node));
        p->Ptrs[0] = prev;
        p->Ptrs[1] = NULL;

        printf("%s\n", nums);
      } 

      if (c == '1') {
        l = 0;
        while (c != '\0') {
          nums[l] = c;
          l++;
          fread(&c, 1, 1, def);
        }
        nums[l] = '\0';
        while (p->Ptrs[1] != NULL) p = p->Ptrs[1];

        p->Strings[1] = strdup(word);

        p = (Node *) malloc(sizeof(Node));
        p->Ptrs[0] = NULL;
        p->Ptrs[1] = prev;

        printf("%s\n", nums);
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
