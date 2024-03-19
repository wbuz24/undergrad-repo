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

/* Read a link from the jdisk */
unsigned short read_link(struct Disk *jd, unsigned short **p, int link) {
  int sector, index;

  /* Calculate the indices of the lba */
  sector = link / (JDISK_SECTOR_SIZE / 2);
  index = link % (JDISK_SECTOR_SIZE / 2);

  /* Only malloc when you need that sector */
  if (p[sector] == NULL) {
    p[sector] = (unsigned short *) malloc(sizeof(unsigned short) * (JDISK_SECTOR_SIZE / 2));
    if (p[sector] == NULL) { fprintf(stderr, "malloc link\n"); exit(1); }
    jdisk_read(jd, link, p[sector]);
  }

//  printf("%hu\n", p[sector][index]);
  
  return p[sector][index];
}

int main(int argc, char **argv) {
  FILE *iofile;
  struct stat buf;
  struct Disk *jd;
  char *dfile, *ifile;
  unsigned short **p;
  int starting_block, exists;
  double lpb, links;
  int s, d, n, i; 
  short unsigned int lba, currlink, arrindex;
  long filesize, flsize;

  /* N - # of sectors is filesize / 1024
   N = S + D
   L = 512 -> 1024/2 -> links per block
   links = D + 1 -> links
   S = ceiling((D+1)/ L) */
  
  if (argc != 4 && argc != 5) { printf("usage: FATRW diskfile import input-file\n       FATRW diskfile export starting-block output-file\n"); exit(1); } 

  /* Attach and error check the jdisk */
  
  dfile = strdup(argv[1]);

  jd = (Disk *) jdisk_attach(dfile);
  if (jd == NULL) { fprintf(stderr, "Invalid jdisk\n"); exit(1); }

  /* Calculate the data sectors */

  if (jdisk_size(jd) % JDISK_SECTOR_SIZE != 0) { fprintf(stderr, "%s is not a proper multiple of 1024\n", dfile); exit(1); }

  n = jdisk_size(jd) / JDISK_SECTOR_SIZE; /* Number of blocks */
  lpb = JDISK_SECTOR_SIZE / 2; /* -> 1024/2 # of links per block */
  d = (lpb * n - 1) / 513; /* Largest possible value that D+S is less than <= disksize*/
  links = d + 1; /* The FAT is comprised of D+1 entries */
  s = ceil(links / lpb); /* Smallest number that can hold D+1 shorts */
  printf("Total Sectors: %d. Data Sectors: %d. FAT Sectors: %d.\n", n, d, s);

  /* Allocate the buffer and an array of pointers that will be my FAT table */
  p = (unsigned short **) malloc(sizeof(unsigned short *) * s);
  if (p == NULL) { fprintf(stderr, "malloc FAT buffer\n"); exit(1); }

  /* Allocate and Store the FAT table */
  for (i = 1; i < s; i++) p[i] = NULL;

  /* You only need to start with the first sector */
  p[0] = (unsigned short *) malloc(sizeof(unsigned short) * lpb);
  if (p[0] == NULL) { fprintf(stderr, "malloc FAT buffer\n"); exit(1); }
  jdisk_read(jd, 0, p[0]);

  currlink = p[0][0];  
  lba = s + currlink - 1;
  printf("New file starts at sector: %d\n", lba);

  /* Store the input file on a jdisk */
  if (argc == 4) {

    /* Check the filesize of the input file and whether the disk has enough free blocks to store the file */
    ifile = strdup(argv[3]);

    iofile = fopen(ifile, "r");
    if (iofile == NULL) { perror(ifile); exit(1); }

    exists = stat(ifile, &buf);
    if (exists < 0) { perror(ifile); exit(1); }

    filesize = buf.st_size;

    /* Determine the number of free blocks */

    flsize = 0;
    while (currlink != 0 && currlink != lba - s + 1) {
      lba = s + currlink - 1; 
      flsize += 1024;

      currlink = read_link(jd, p, lba);
    }

    /* Calculate the amount of bytes in the last free block */

    /* If the file is larger than free blocks, throw an error */
    if (flsize < filesize) { fprintf(stderr, "Not enough free blocks\n"); exit(1); }


    printf("Reads: %ld\nWrites: %ld\n", jdisk_reads(jd), jdisk_writes(jd));

    fclose(iofile);
    free(ifile);
  }
  if (argc == 5) {
    /* Find the file at the starting block and write to the output file */
  
  }

  jdisk_unattach(jd);
  free(p);
  free(dfile);
}
