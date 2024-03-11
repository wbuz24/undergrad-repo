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

char* grab_path(char *absolute) {
  int i, len;

  /* Find the index of the last / in the absolute
   * path and return a pointer to it */
  len = strlen(absolute);
  for (i = len - 1; i >= 0; i--) {
    if (absolute[i] == '/') return absolute + i + 1; 
  } 

  return absolute;
}

void directory_traverse(char *pathname, JRB inodes) {
  DIR *d;
  struct dirent *de;
  struct stat buf;
  FILE *file;
  int exists, fn_size, dir_fn_size, sz, suff_size;
  int fname, fmode;
  long in, mtime, filesize;
  char *dir_fn, *bytes, *suffix, *relative;

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

  /* Just a pointer to the suffix of the absolute path */
  suffix = grab_path(dir_fn);
  relative = (char *) malloc(sizeof(char) * dir_fn_size + 10);
  suff_size = strlen(suffix);
  strcpy(relative, suffix);
  strcat(relative + suff_size, "/");

  /* Run through the entire directory */
  for (de = readdir(d); de != NULL; de = readdir(d)) {

    /* Reallocate for the size of the filename */
    sz = strlen(de->d_name);
    if (dir_fn_size < fn_size + sz + 2) {
      dir_fn_size = fn_size + sz + 10;
      dir_fn = realloc(dir_fn, dir_fn_size);
    }

    /* Add the suffix after the / */
    strcpy(dir_fn + fn_size + 1, de->d_name);

    /* Check the existence of each file */
    exists = stat(dir_fn, &buf);
    if (exists < 0) { fprintf(stderr, "Could'nt open %s\n", dir_fn); continue; }
    /* We don't care about . and .. */
    if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {

      /* Print the size of the file's name, as a four-byte integer in little endian */
      fname = strlen(dir_fn);
      fwrite(&fname, 4, 1, stdout);
      /* Print the file's name, no null character */
      fwrite(dir_fn, 1, fname,  stdout); 
      /* Print the file's inode as an eight byte long in little endian */
      fwrite(&buf.st_ino, 8, 1, stdout);

      /* If you haven't seen the inode before */
      if (jrb_find_gen(inodes, new_jval_l(buf.st_ino), compare) == NULL) {
        /* Add it */
        jrb_insert_gen(inodes, new_jval_l(buf.st_ino), new_jval_i(0), compare);

        /* Print the file's mode as a four byte integer in little endian */
        fwrite(&buf.st_mode, 4, 1, stdout);
        /* Print the file's lst modification time, in seconds, as an eight byte long in little endian */
        fwrite(&buf.st_mtime, 8, 1, stdout);
      }

      /* Attempt to open the sub directory */
      if (S_ISDIR(buf.st_mode)) {
        /* Construct the relative path */
        strcat(relative + suff_size + 1, de->d_name);
        printf("\n\n\n%s   %s\n\n\n", relative, dir_fn);
        directory_traverse(relative, inodes);
      }
      else {
        /* Print the file's size as an eight byte long in little endian */
        fwrite(&buf.st_size, 8, 1, stdout);

        /* Open the file and error check */
        file = fopen(dir_fn, "r");
        if (file == NULL) { perror(dir_fn); exit(1); }
        bytes = (char *) malloc(sizeof(char) * buf.st_size + 10);
        fread(bytes, 1, buf.st_size, file);
        fwrite(bytes, 1, buf.st_size, stdout); 

        free(bytes);
        fclose(file);
      }
    }
  }

  /* Free the memory */
  closedir(d);
  free(relative);
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
