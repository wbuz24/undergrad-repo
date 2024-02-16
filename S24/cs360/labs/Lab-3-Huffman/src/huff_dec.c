/* Lab 3 
   Will Buziak
   CS360
   Hex dump */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* recursive free, call on children then free node */

typedef struct huff_node {
  struct huff_node *Ptrs[2];
  char *Strings[2];
} Node;

void freeNodes(Node *n) {

  if (n->Ptrs[0] != NULL) freeNodes(n->Ptrs[0]);
  if (n->Ptrs[1] != NULL) freeNodes(n->Ptrs[1]);

  if (n->Strings[0] != NULL) printf("%s\n", n->Strings[0]);
  if (n->Strings[1] != NULL) printf("%s\n", n->Strings[1]);
  free(n);

  return;
}

int main(int argc, char **argv) {
  FILE *def, *input; // file pointer
  char c, h;
  char word[1000];
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
    n->Strings[0] = NULL;
    n->Strings[1] = NULL;


  while (fread(&c, 1, 1, def) > 0) {
      /* p is the node being processed */
      p = n;
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
      if (c == '0' || c == '1') {
        /* Chase nodes until you find the null character */
        while (c != '\0') {
          h = c; // grab the last character
          if (c == '0') {
            /* If the zero pointer is set, chase it, otherwise make a new node */
            if (p->Ptrs[0] != NULL) p = p->Ptrs[0];
            if (p->Strings[0] == NULL) {
              prev = p;
              p = (Node *) malloc(sizeof(Node));
              p->Ptrs[0] = prev;
              p->Ptrs[1] = NULL;
            }
          }
          if (c == '1') {
            if (p->Ptrs[1] != NULL) p = p->Ptrs[1];
            if (p->Strings[1] == NULL) {
              prev = p;
              p = (Node *) malloc(sizeof(Node));
              p->Ptrs[0] = NULL;
              p->Ptrs[1] = prev;
            }
          }
          fread(&c, 1, 1, def);
        }
        /* Check the value that got you here and copy the word */
        if (h == '0') p->Strings[0] = strdup(word);
        if (h == '1') p->Strings[1] = strdup(word);
      } 
    }

    /* do a DFS, freeing the nodes from the bottom up */
    freeNodes(n);
  }


  return 1;
}
