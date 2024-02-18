/* Will Buziak 
 * CS494
 * LZ77 Compression */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* shift the window */
char shiftWin(char buff[], int w, FILE *f) {
  int i;
  char new[w];
  char next;

  /* copy the bit one place over */
  for (i = 1; i < w; i++) new[i-1] = buff[i];
  fread(&next, 1, 1, f);
  new[i] = next;

  return new;
}

int strmatch(const char *search, const char *window) {
  
  /* Return the longest match in the search buffer */
  return 0;
}

int main(int argc, char **argv) {
  FILE *input;
  long long s, w; /* size of the search and look ahead buffer */
  char c; 

  /* Read in files on command line */
  if (argc != 5) {
    printf("./bin/LZ77 search window input.txt output.txt");
    return 0;
  }

  sscanf(argv[1], "%lld", &s);
  sscanf(argv[2], "%lld", &w);

  if (s <= 0 || w <= 0 || s > 4096 || w > 18) {
    printf("Buffer out of bounds\nsearch: %lld\nwindow: %lld\n", s, w);
    return 0;
  }
  printf("Search size: %lld Window size: %lld\n\n", s, w);

  /* Statically declare buffer size */
  char search[s];
  char window[w];

  input = fopen(argv[3], "r");
  if (input == NULL) {
    printf("File did not open properly\n");
    return 0;
  }

  while (fread(&c, 1, 1, input) > 0) {
    
  }

  /* While reading in a file
      * Find the longest match from input in the search buffer
      * read to the file the triple or duple (d, r, c)
      * move the cursor
   * */

  free(search);
  free(window);
  return 1;
}
