/*************************** Will Buziak ********************************/
/***************************    CS360    ********************************/
/***************************    Lab 2    ********************************/
/***************************    Tarx     ********************************/
/***************************             ********************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>
#include <string.h>
#include "jrb.h"

/* Comparison function for JRB tree */
int compare(Jval v1, Jval v2) {
  if (v1.l < v2.l) return -1;
  if (v1.l > v2.l) return 1;
  return 0;
}

void build_directory(JRB inodes, JRB modes, JRB modtimes) {
  unsigned int fnsize, flmode, file_size;
  long inode, modtime;
  uint64_t flsize, err;
  char *filename, *bytes;
  FILE *ofile;
  JRB tmp;
  
  file_size = 0;
  /* Only read in the filename size */
  err = fread(&fnsize, 1, 4, stdin);
  while (err == 4) {

    /* allocate or reallocate space for the filename */
    filename = (char *) malloc(sizeof(char) * fnsize + 10);
    if (filename == NULL) { perror(filename); exit(1); }

    /* Read in the filename */
    if (fread(filename, 1, fnsize, stdin) != fnsize) { fprintf(stderr, "Bad tarc file, couldn't read filename\n"); exit(1); }
    if (fread(&inode, 1, 8, stdin) != 8) { fprintf(stderr, "Bad tarc file at %s, couldn't read inode\n", filename); exit(1); }

    /* Set null character */

    filename[fnsize] = '\0';

    /* Check if it is a new inode */
    tmp = jrb_find_gen(inodes, new_jval_l(inode), compare);

    if (tmp == NULL) { 
      /* If it is a new inode, it will include it's mode and modtime */
      if (fread(&flmode, 1, 4, stdin) != 4) { fprintf(stderr, "Bad tarc file at %s, couldn't read mode\n", filename); exit(1); }
      if (fread(&modtime, 1, 8, stdin) != 8) { fprintf(stderr, "Bad tarc file at %s, couldn't read modification time\n", filename); exit(1); }

      /* Insert into the red-black tree */
      jrb_insert_gen(inodes, new_jval_l(inode), new_jval_s(filename), compare);

      /* Build the file or directory */

      if (S_ISDIR(flmode)) {
        /* Directory */
        mkdir(filename, 766);        
      }
      else if (S_ISREG(flmode)) {
        /* This is a file */
        if (fread(&flsize, 8, 1, stdin) != 1) { fprintf(stderr, "Bad tarc file at %s, couldn't read the file size\n", filename); exit(1); }

        /* Read in the bytes then write them to the new file */
        bytes = (char*)malloc((flsize + 10) * sizeof(char));
        if (bytes == NULL && flsize != 0) {
          printf("null bytes");
          exit(1);
        }
        err = fread(bytes, 1, flsize, stdin);
        if (err < flsize) { fprintf(stderr, "Bad tarc file at %s, read %lu out of %lu bytes\n", filename, err, flsize); exit(1); }

        /* Create new file */
        ofile = fopen(filename, "w");
        if (ofile == NULL) { perror(filename); exit(1); }

        /* Write bytes */
        fwrite(bytes, 1, flsize, ofile);

        /* Immediately close file to save on File descriptors */
        fclose(ofile);
        free(bytes);
      }
    } 
    else {
      /* Create a link between the files */
      link(tmp->val.s, filename);
      if (link < 0) { perror(filename); exit(1); }
     }

     if (jrb_find_str(modes, filename) == NULL && tmp == NULL) {
       jrb_insert_str(modes, filename, new_jval_i(flmode));
       jrb_insert_str(modtimes, filename, new_jval_l(modtime));
     }

     err = fread(&fnsize, 1, 4, stdin);
  }
  if (err > 0 && err < 4) { fprintf(stderr, "Bad tarc file at byte  tried to read filename, but only got %lu\n", err); exit(1); }
}

int main() {
  JRB inodes, modes, modtimes, tmp;
  struct stat buf;
  struct timeval times[2];
  int exists;

  /* File is read on standard input */

  inodes = make_jrb();
  modes = make_jrb();
  modtimes = make_jrb();

  build_directory(inodes, modes, modtimes);

  /* After all is said & done, go through and change all protection modes */

  jrb_traverse(tmp, modtimes) {
    exists = lstat(tmp->key.s, &buf);
    //if (exists < 0) { fprintf(stderr, "cannot stat %s\n", tmp->key.s); exit(1); }


    /* Change modtime */
    times[0].tv_sec = buf.st_mtime;
    times[1].tv_sec = tmp->val.l;
    times[1].tv_usec = 0; 
    utimes(tmp->key.s, times);
  }
  jrb_traverse(tmp, modes) {
    chmod(tmp->key.s, tmp->val.i);

    free(tmp->key.s);
  }

  jrb_free_tree(modes);
  jrb_free_tree(inodes);
  jrb_free_tree(modtimes);

  return 1;
}
