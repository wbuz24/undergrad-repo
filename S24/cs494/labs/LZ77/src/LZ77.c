/* Will Buziak 
 * CS494
 * LZ77 Compression */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* shift the window */
char* shiftWin(char *buff, int size, char next) {
  int i;
  char *new;

  new = (char *) malloc (sizeof(char) * size);
  /* copy the byte one place over */
  for (i = 1; i < size; i++) new[i-1] = buff[i];
  /* Set the last byte */
  new[size - 1] = next;

  free(buff);

  return new;
}

int strmatch(const char *search, const char *window) {
  (void) search;
  (void) window;  
  /* Return the longest match in the search buffer */
  return 0;
}

int main(int argc, char **argv) {
  FILE *input, *output;
  char *search, *window;
  long long s, w; /* size of the search and look ahead buffer */
  char c, last; 

  /* Read in files on command line */
  if (argc != 5) {
    printf("./bin/LZ77 search window input.txt output.txt\n");
    return 0;
  }

  /* Read command line args for buffer sizes */
  sscanf(argv[1], "%lld", &s);
  sscanf(argv[2], "%lld", &w);

  /* Check the buffer sizes */
  if (s <= 0 || w <= 0 || (s + w) > 4096) {
    printf("Buffer out of bounds\nsearch: %lld\nwindow: %lld\n", s, w);
    return 0;
  }
  printf("Search size: %lld\nWindow size: %lld\n\n", s, w);

  /* Declare buffer size by calling malloc */
  search = (char *) malloc(sizeof(char) * s);
  window  = (char *) malloc(sizeof(char) * w);

  /* Open the input file */
  input = fopen(argv[3], "r");
  if (input == NULL) {
    printf("File did not open properly\n");
    return 0;
  }


  output = fopen(argv[4], "w");

  /* Current pointer is always the first index of the window */
  while (fread(&c, 1, 1, input) > 0) {
    last = window[0];
    window = shiftWin(window, w, c);
    search = shiftWin(search, s, last);

    /* No need to decode newlines, null characters and spaces, just output them directly to file */
    if (window[0] == ' ' || window[0] == '\n' || window[0] == '\0') {
      last = window[0];
      fprintf(output, "%c", last);
    }

    /* Find the longest match in the buffers */ 
    /* Print the appropriate encoding to the output file */
    
  }

  /* While reading in a file
      * Find the longest match from input in the search buffer
      * read to the file the triple or duple (d, r, c)
      * move the cursor
   * */

  free(search);
  free(window);
  fclose(input);
  fclose(output);
  return 1;
}
