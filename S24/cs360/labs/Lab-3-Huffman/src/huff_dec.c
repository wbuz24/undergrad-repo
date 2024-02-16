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

void freeNodes(Node *n) {

  /* recursive free, call on children then free node */
  if (n->Ptrs[0] != NULL) freeNodes(n->Ptrs[0]);
  if (n->Ptrs[1] != NULL) freeNodes(n->Ptrs[1]);

  /* Free strings */
  if (n->Strings[0] != NULL) {
    free(n->Strings[0]);
  }

  if (n->Strings[1] != NULL) {
    free(n->Strings[1]);
  }

  /* Free nodes */
  free(n);

  return;
}

/* recursive printing for testing */
void print_tree(Node *root) {
  if (root->Ptrs[0] != NULL) print_tree(root->Ptrs[0]);
  if (root->Ptrs[1] != NULL) print_tree(root->Ptrs[1]);

  if (root->Strings[0] != NULL) printf("%s\n", root->Strings[0]);
  if (root->Strings[1] != NULL) printf("%s\n", root->Strings[1]);
}

void insert_into_tree(Node *root, char *bitstring, char *decoding) {
  Node *prev, *p;
    
  /* If this is the last bit, insert the word */
  if (strlen(bitstring) == 1) {
    if (*bitstring == '0') root->Strings[0] = strdup(decoding);
    if (*bitstring == '1') root->Strings[1] = strdup(decoding);
  }

  else {
    /* Bit is zero */
    if (*bitstring == '0') {
    /* Chase the pointer */
      if (root->Ptrs[0] != NULL) insert_into_tree(root->Ptrs[0], bitstring+1, decoding);
    /* Create the Node and recursive call */
      else {
        prev = root;
        p = (Node *) malloc(sizeof(Node));
        p->Ptrs[0] = NULL;
        p->Ptrs[1] = NULL;
        p->Strings[0] = NULL;
        p->Strings[1] = NULL;
        prev->Ptrs[0] = p;
        insert_into_tree(p, bitstring+1, decoding); 
      }
    }
    /* Bit is one */
    if (*bitstring == '1') {
      if (root->Ptrs[1] != NULL) insert_into_tree(root->Ptrs[1], bitstring+1, decoding); 
      else {
        prev = root;
        p = (Node *) malloc(sizeof(Node));
        p->Ptrs[0] = NULL;
        p->Ptrs[1] = NULL;
        p->Strings[0] = NULL;
        p->Strings[1] = NULL;     
        prev->Ptrs[1] = p;
        insert_into_tree(p, bitstring+1, decoding);
      }
    }
  }
}

/* Grab the next bit and return it */
int get_bit(char *buff, int n) {
  int nth, ret;

  nth = n / 8;
  ret = (buff[nth] >> (n % 8)) & 1;

  if (ret > 0) return 1;
  else return 0;
}


int main(int argc, char **argv) {
  FILE *def, *input; // file pointer
  char c;
  char *d;
  char word[1000], nums[1000];
  int i, l;
  u_int32_t last, bytes;
  Node *n, *p;

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
  l = ftell(input); // total
  
/*  if (l < 4) {
    fprintf(stderr, "Error: file is not the correct size.\n");
    return 0;
  }*/
  fread(&last, 1, 4, input);
  fseek(input, 0, SEEK_SET);

  bytes = last / 8 + 4; // # of bytes
  
//  printf("%d %u\n\n", l * 8, last);

  if (l > (int) last) fprintf(stderr, "Error: file is not the correct size.\n");
  else {
    
    /* Create the bottom node in the tree, n */
    n = (Node *) malloc(sizeof(Node));
    n->Ptrs[0] = NULL;
    n->Ptrs[1] = NULL;
    n->Strings[0] = NULL;
    n->Strings[1] = NULL;

    while (fread(&c, 1, 1, def) > 0) {
      /* p is the node being processed */
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
        /* Store the number into a buffer */
        l = 0;
        while (c != '\0') {
          nums[l] = c;
          l++;
          fread(&c, 1, 1, def);
        } 
        nums[l] = '\0';
        /* Insert into a tree */
        insert_into_tree(n, nums, word);
      }
    }

    //print_tree(n);
    /* Read in bytes from the input file */

    d = (char *) malloc(sizeof(char) * bytes + 1);
    fread(d, 1, bytes, input);
    p = n;

    for (i = 0; i < (int) last; i++) {
      l = get_bit(d, i);
      //printf("%d", l);
      if (!l && p->Ptrs[0] != NULL) p = p->Ptrs[0];
      else if (!l) {
        printf("%s", p->Strings[0]);
        p = n;
      }

      if (l && p->Ptrs[1] != NULL) p = p->Ptrs[1];
      else if (l) {
        printf("%s", p->Strings[1]);
        p = n;
      }      
    }

//    printf("\n\n");

    // print_tree(n);

    /* do a DFS, freeing the nodes from the bottom up */
    free(d);
    freeNodes(n);
    fclose(def);
    fclose(input);
  }

  return 1;
}
