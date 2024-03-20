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

/* Read a link from the jdisk and return the dereferenced bytes */
unsigned short read_link(struct Disk *jd, unsigned short **p, int link) {
  int index, sector;

  /* Calculate the indices of into the FAT */ 
  sector = link / 512;
  index = link % 512;

  /* Only allocate and read a sector when necessary */
  if (p[sector] == NULL) {
    p[sector] = (unsigned short *) malloc(sizeof(unsigned short) * (JDISK_SECTOR_SIZE / 2));
    if (p[sector] == NULL) { fprintf(stderr, "malloc link\n"); exit(1); }
    jdisk_read(jd, sector, p[sector]);
  }

  return p[sector][index];
}

/* Write a link to the FAT table, later this will be written to the disk */
int write_link(unsigned short **p, int link, unsigned short val) {
  int sector, index;
  unsigned short nextlink;

  sector = link / 512;
  index = link % 512; 
  /* Set the value at the current link to 0 in the FAT table */

  p[sector][index] = 0;

  /* Set the first link in the FAT to the sector after this one */
  p[0][0] = val;  
  
  /* Track the sector you are making changes */
  return sector;
}

/* Write the FAT sectors back to the jdisk */
void flush_links(struct Disk *jd, unsigned short **p, int sector) {
  /* You only need to call jdisk_write on two FAT sectors */

  if (sector != 0) {
    jdisk_write(jd, sector, p[sector]);
  }

  jdisk_write(jd, 0, p[0]);
}

int main(int argc, char **argv) {
  FILE *iofile;
  struct stat buf;
  struct Disk *jd;
  char *dfile, *ifile;
  unsigned short **p, *bytes;
  int starting_block, exists, last1, last2;
  double lpb, links;
  int s, d, n, i, x, sector, flag, newsec; 
  short unsigned int lba, currlink, nextlink, fin, pen;
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
  d = (lpb * n - 1) / 513; /* Data sectors */
  links = d + 1; /* The FAT is comprised of D+1 entries */
  s = ceil(links / lpb); /* FAT sectors */
  // printf("Total Sectors: %d. Data Sectors: %d. FAT Sectors: %d.\n", n, d, s);

  /* Allocate the buffer and an array of pointers that will be my FAT table */
  p = (unsigned short **) malloc(sizeof(unsigned short *) * s);
  if (p == NULL) { fprintf(stderr, "malloc FAT buffer\n"); exit(1); }

  bytes = (unsigned short *) malloc(sizeof(unsigned short) * 512);
  if (bytes == NULL) { fprintf(stderr, "malloc fileread buffer\n"); exit(1); }

  /* Allocate and Store the FAT table */
  for (i = 0; i < s; i++) p[i] = NULL;

  /* You only need to start with the first sector */
  p[0] = (unsigned short *) malloc(sizeof(unsigned short) * lpb);
  if (p[0] == NULL) { fprintf(stderr, "malloc FAT buffer\n"); exit(1); }
  jdisk_read(jd, 0, p[0]);

  currlink = read_link(jd, p, 0); /* Start of the free list */  
  newsec = s + currlink - 1;

  /* Import a file on a jdisk */
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
    while (currlink != 0) {
      nextlink = read_link(jd, p, currlink);
      /* Only run so long as you need to */
      flsize += 1024;
      if (flsize >= filesize || currlink == nextlink) break;

      currlink = nextlink;
    }

    flsize += 1024;

    if (flsize < filesize) { fprintf(stderr, "Not enough free blocks (%d) for %s, which needs %d\n", ((filesize - flsize) / 1024) + 1, ifile, (filesize / 1024) + 1); exit(1); }

    /* Write blocks back to the jdisk */

    flag = 0;
    currlink = read_link(jd, p, 0); // FAT index 
    while (filesize != 0) {
      lba = currlink + s - 1; // index of the disk you will read

      /* Read file's bytes into a buffer */
      fread(bytes, 1, (filesize > 1024) ? 1024 : filesize, iofile);

      /* Write the buffer's bytes onto the jdisk */
      jdisk_write(jd, lba, bytes);

      /* Final block of the file, reset the fat and return the sector that changed */
      if (filesize <= 1024) {
        sector = write_link(p, currlink, read_link(jd, p, currlink));
      }

      /* Update the size - if the size is greater that 1024, subtract, otherwise set it to zero */
      filesize = (filesize > 1024) ? filesize - 1024 : 0; 
      currlink = read_link(jd, p, currlink);
    }

    /* Actually call jdisk_write */

    flush_links(jd, p, sector);

    printf("New file starts at sector: %d\n", newsec);
    printf("Reads: %ld\nWrites: %ld\n", jdisk_reads(jd), jdisk_writes(jd));

    fclose(iofile);
    free(ifile);
  }
  if (argc == 5) {
    /* Find the file at the starting block and write to the output file */


    /* Last block in the file may not be 1024 bytes */
      /* Calculate the amount of bytes in the last free block */
        /* Build the bytes in the sector with the last two bytes */
    /*
    if (currlink != 0) {
      if (p[currlink][1023] == 0xff) flsize += 1023;
      else {
        last1 = (currlink * 1024) - 1;
        last2 = last1 - 1;

        fin = read_link(jd, p, last1);
        pen = read_link(jd, p, last2);
        flsize += fin * 256 + pen;
//        printf("%hu %hu", pen, fin);
      }
    }*/
  
  }

  jdisk_unattach(jd);
  free(p);
  free(dfile);
}
