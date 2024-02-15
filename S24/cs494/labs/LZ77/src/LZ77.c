/* Will Buziak 
 * CS494
 * LZ77 Compression */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *input;
  long long s, w; /* size of the search and look ahead buffer */
  char *search, *window;

  /* Read in files on command line */
  if (argc != 5) {
    printf("./bin/LZ77 search window input.txt output.txt");
    return 0;
  }

  sscanf(argv[1], "%lld", &s);
  sscanf(argv[2], "%lld", &w);

  if (s <= 0 || w <= 0) {
    printf("Buffer out of bounds\nsearch: %lld\nwindow: %lld\n", s, w);
    return 0;
  }

  search = (char *) malloc(sizeof(char) * s);
  window = (char *) malloc(sizeof(char) * s);

  input = fopen(argv[3], "r");
  if (input == NULL) {
    printf("File did not open properly\n");
    return 0;
  }


  printf("%lld %lld\n", s, w);

  free(search);
  free(window);
  return 1;
}
