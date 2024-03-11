/* Will Buziak */
/* CS494 */
/* Lab 2 */
/* File Allocation Table - Read and Write */

#include <stdio.h>
#include <stdlib.h>
#include "jdisk.h"

int main(int argc, char **argv) {
  FILE *diskfile, *iofile;
  char *dfile;
  int starting_block;
  
  // N - # of sectors is filesize / 1024
  // N = S + D
  // L = 512 -> 1024/2 -> links per block
  // links = D + 1 -> links
  // S = ceiling((D+1)/ L) 
  
  if (argc != 4 && argc != 5) { printf("FATRW diskfile import input-file\nFATRW diskfile export starting-block output-file\n"); exit(1); } 

  /* Open and error check the diskfile */
  diskfile = fopen(argv[1], "r+");
  if (diskfile == NULL) { perror(argv[1]); exit(1); }

  if (argc == 4) {
    /* Store the input file on a jdisk */
  }
  if (argc == 5) {
    /* Find the file at the starting block and write to the output file */
  
  }

}
