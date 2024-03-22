/*************************** Will Buziak ********************************/
/***************************    CS360    ********************************/
/***************************    Lab 2    ********************************/
/***************************    Tarx     ********************************/
/***************************             ********************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "jrb.h"

/* Comparison function for JRB tree */
int compare(Jval v1, Jval v2) {
  if (v1.l < v2.l) return -1;
  if (v1.l > v2.l) return 1;
  return 0;
}

void build_directory(JRB inodes) {
  int fnsize, flmode, rel_size, file_size;
  long inode, modtime, flsize;
  char *filename, *bytes;
  DIR *d;
  struct direct *de;

  /* Only read in the filename size */
  rel_size = 0;
  file_size = 0;
  while (fread(&fnsize, 4, 1, stdin)) {

    /* allocate or reallocate space for the filename */
    if (rel_size == 0) {
      filename = (char *) malloc(sizeof(char) * fnsize + 10);
      if (filename == NULL) { perror(filename); exit(1); }
      rel_size = fnsize + 10;
    }
    else if (rel_size < fnsize + 10) {
      filename = realloc(filename, fnsize + 10);
      rel_size = fnsize + 10;
    }

    /* Read in the filename */
    fread(filename, 1, fnsize, stdin);
    fread(&inode, 8, 1, stdin);

    printf("%s\n", filename);

    /* Check if it is a new inode */

    if (jrb_find_gen(inodes, new_jval_l(inode), compare) == NULL) { 

      fread(&flmode, 4, 1, stdin);
      fread(&modtime, 8, 1, stdin);

      /* Insert into the red-black tree */
      jrb_insert_gen(inodes, new_jval_l(inode), new_jval_i(flmode), compare);

      if (S_ISDIR(flmode)) {
        /* Directory */
//        build_directory(inodes);
      }
      else {
        /* This is a file */
        fread(&flsize, 8, 1, stdin);

        /* Allocate or reallocate the files bytes */
        if (file_size == 0) {
          bytes = (char *) malloc(sizeof(char) * flsize + 10);
          if (bytes == NULL) { perror("malloc files bytes\n"); exit(1); }
          file_size = flsize;
        }
        else if (file_size < flsize + 10) {
          bytes = realloc(bytes, flsize + 10);
          file_size = flsize;
        }

        /* Read in the bytes */
        fread(bytes, 1, flsize, stdin);

      //  printf("%d %s\n", flsize, bytes);
      }
    }
  }

  free(bytes);
  free(filename);
}

int main() {
  JRB inodes;

  /* File is read on standard input */

  inodes = make_jrb();

  build_directory(inodes);

  jrb_free_tree(inodes);

  return 1;
}
