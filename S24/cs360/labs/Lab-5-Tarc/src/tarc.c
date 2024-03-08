/* Will Buziak */
/* CS360 */
/* Lab-5 */
/* Tarc */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "fields.h"
#include "dllist.h"
#include "jrb.h"

/* Comparison function for JRB tree */
int compare(Jval v1, Jval v2) {
  if (v1.l < v2.l) return -1;
  if (v1.l < v2.l) return 1;
  return 0;
}

void directory_traverse(char *pathname, JRB inodes) {
  DIR *d;
  struct dirent *de;
  struct stat buf;
  FILE *file;
  int exists, fn_size, dir_fn_size, sz;
  char *dir_fn;

  /* Attempt to open the directory */
  d = opendir(pathname);
  if (d == NULL) { perror(pathname); exit(1); }

  /* Construct the entire pathname */
  fn_size = strlen(pathname);
  dir_fn_size = fn_size + 10;
  dir_fn = (char *) malloc(sizeof(char) * dir_fn_size);
  if (dir_fn == NULL) { perror(dir_fn); exit(1); }
  strcpy(dir_fn, pathname);
  strcat(dir_fn + fn_size, "/");

  /* Run through the entire directory */
  for (de = readdir(d); de != NULL; de = readdir(d)) {

    /* Reallocate for the size of the filename */
    sz = strlen(de->d_name);
    if (dir_fn_size < fn_size + sz + 2) {
      dir_fn_size = fn_size + sz + 10;
      dir_fn = realloc(dir_fn, dir_fn_size);
    }

    /* Add the suffix */
    strcpy(dir_fn + fn_size + 1, de->d_name);

    /* Attempt to open each file */
    exists = stat(dir_fn, &buf);
    if (exists < 0) { fprintf(stderr, "Could'nt open %s\n", dir_fn); continue; }
    /* We don't care about . and .. */
    if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {

      /* Print the size of the file's name, as a four-byte integer in little endian */
      /* Print the file's name, no null character */
      printf("%s\n", dir_fn);
      /* Print the file's inode as an eight byte long in little endian */

      /* If you haven't seen the inode before */
      if (jrb_find_gen(inodes, new_jval_l(buf.st_ino), compare) == NULL) {
        /* Add it */
        jrb_insert_gen(inodes, new_jval_l(buf.st_ino), new_jval_i(0), compare);

        /* Print the file's mode as a four byte integer in little endian */
        /* Print the file's lst modification time, in seconds, as an eight byte long in little endian */
      }

      /* Attempt to open the sub directory */
      if (S_ISDIR(buf.st_mode)) directory_traverse(dir_fn, inodes);
      else {
        /* Print the file's size as an eight byte long in little endian */

        /* Open the file and error check */
        file = fopen(dir_fn, "r");
        if (file == NULL) { perror(dir_fn); exit(1); }
      }
    }
  }

  /* Free the memory */
  closedir(d);
  free(dir_fn);
}

int main(int argc, char** argv) {
  char *pathname;
  JRB inodes;

  if (argc != 2) { fprintf(stderr, "./bin/tarc directory/\n"); exit(1); }

  /* Grab the pathname */
  pathname = strdup(argv[1]); 

  inodes = make_jrb();
  /* Recursively search the directory for files and subdirectories */
  directory_traverse(pathname, inodes);

  free(pathname);
  jrb_free_tree(inodes);

  return 1;
}
