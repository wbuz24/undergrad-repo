/* Will Buziak */
/* CS494 */
/* Lab 2 */
/* File Allocation Table - Read and Write */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <string.h>
#include "jdisk.h"

int main(int argc, char **argv) {
  FILE *iofile;
  struct stat buf;
  char *dfile;
  int starting_block, exists;
  double lpb, links;
  int s, d, n; 
  
  /* N - # of sectors is filesize / 1024
  // N = S + D
  // L = 512 -> 1024/2 -> links per block
  // links = D + 1 -> links
   S = ceiling((D+1)/ L) */
  
  if (argc != 4 && argc != 5) { printf("FATRW diskfile import input-file\nFATRW diskfile export starting-block output-file\n"); exit(1); } 

  /* Attach and error check the jdisk */
  
  dfile = strdup(argv[1]);
  exists = stat(dfile, &buf);
  if (exists < 0) { fprintf(stderr, "Couldn't stat diskfile: %s\n", dfile); exit(1); }


  /* Calculate the data sectors */

  n = buf.st_size / 1024;
  lpb = 512; // -> 1024/2
  d = (512 * n - 1) / 513;
  links = d + 1;
  s = ceil(links / lpb);

  printf("N: %d\nS: %d\nD: %d\nLPB: %f\nLinks: %f\n", n, s, d, lpb, links);

  if (argc == 4) {
    /* Store the input file on a jdisk */
  }
  if (argc == 5) {
    /* Find the file at the starting block and write to the output file */
  
  }

}
