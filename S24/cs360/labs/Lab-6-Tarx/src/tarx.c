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

void build_directory(JRB inodes, JRB modes) {
  int fnsize, flmode, file_size;
  long inode, modtime, flsize;
  char *filename, *bytes;
  FILE *ofile;
  JRB tmp;
  
  file_size = 0;
  /* Only read in the filename size */
  while (fread(&fnsize, 4, 1, stdin) == 1) {

    /* allocate or reallocate space for the filename */
    filename = (char *) malloc(sizeof(char) * fnsize + 10);
    if (filename == NULL) { perror(filename); exit(1); }

    /* Read in the filename */
    fread(filename, 1, fnsize, stdin);
    fread(&inode, 8, 1, stdin);

    /* Set null character for printing */
    filename[fnsize] = '\0';

    /* Check if it is a new inode */
    tmp = jrb_find_gen(inodes, new_jval_l(inode), compare);

    if (tmp == NULL) { 
      /* If it is a new inode, it will include it's mode and modtime */
      fread(&flmode, 4, 1, stdin);
      fread(&modtime, 8, 1, stdin);

      /* Insert into the red-black tree */
      jrb_insert_gen(inodes, new_jval_l(inode), new_jval_i(flmode), compare);
    }
    else flmode = tmp->val.i; 

    if (S_ISDIR(flmode)) {
      /* Directory */
      mkdir(filename, 00744);        
      jrb_insert_str(modes, filename, new_jval_i(flmode));
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
      bytes[flsize] = '\0';

      ofile = fopen(filename, "w");
      if (ofile == NULL) { perror(filename); exit(1); }

      fwrite(bytes, 1, flsize, ofile);

      fclose(ofile);
      //printf("%d\n", fnsize);
      //printf("%s\n", filename);
      //printf("%ld\n", inode);

      //printf("%ld\n", flsize);
      //printf("%s\n", bytes);
      chmod(filename, flmode);
    }
    /* Adjust mod times and r/w protection at the end */
    //printf("%d\n%ld\n", flmode, modtime);

  }

  free(bytes);
}

int main() {
  JRB inodes, modes, tmp;

  /* File is read on standard input */

  inodes = make_jrb();
  modes = make_jrb();

  build_directory(inodes, modes);

  jrb_traverse(tmp, modes) {
    printf("%s\n", tmp->key.s);
    chmod(tmp->key.s, tmp->val.i);

  }

  jrb_free_tree(inodes);

  return 1;
}
