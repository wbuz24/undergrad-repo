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
  if (v1.l > v2.l) return 1;
  return 0;
}

char* grab_path(char *absolute) {
  int i, len;

  /* Find the index of the last / in the absolute
   * path and return a pointer to it */
  len = strlen(absolute);
  for (i = len - 2; i >= 0; i--) {
    if (absolute[i] == '/') return absolute + i + 1; 
  } 

  return absolute;
}

void directory_traverse(char *fn, JRB inodes, char *relative) {
  DIR *d;              
  struct dirent *de;     
  struct stat buf;          
  FILE *file;

  char *dir_fn, *bytes, *rel_fn, *suffix; 
  int dir_fn_size, sz, fn_size, suff_size, exists, rel_size, fname;

  Dllist directories, tmp;  /* Dllist of directory names, for doing recusion after closing. */

  /* Initialize */
  d = opendir(fn);
  if (d == NULL) {
    perror(fn);
    exit(1);
  }
  directories = new_dllist();

  /* allocate space for the absolute path and the relative path */
  fn_size = strlen(fn);
  dir_fn_size = fn_size + 10;
  dir_fn = (char *) malloc(sizeof(char) * dir_fn_size);
  if (dir_fn == NULL) { perror("malloc dir_fn"); exit(1); }
  strcpy(dir_fn, fn);
  strcat(dir_fn + fn_size, "/");

  suff_size = strlen(relative);
  rel_size = suff_size + 10;
  rel_fn = (char *) malloc(sizeof(char) * rel_size);
  if (rel_fn == NULL) { perror("malloc rel_fn"); exit(1); }
  strcpy(rel_fn, relative);
  strcat(rel_fn + suff_size, "/");

  /* Run through the directory and run stat() on each file, 
     keeping track of the total size of all of the files.  */
  for (de = readdir(d); de != NULL; de = readdir(d)) {

    /* We disregard . & .. */
    if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
      /* Reallocate space for the absolute and relative path to include the filename */
      sz = strlen(de->d_name);
      if (dir_fn_size < fn_size + sz + 2) {    /* The +2 is for the slash and null character. */
        dir_fn_size = fn_size + sz + 10;
        dir_fn = realloc(dir_fn, dir_fn_size);
      }
      strcpy(dir_fn + fn_size + 1, de->d_name);

      if (rel_size < suff_size + sz + 2) {
        rel_size = suff_size + sz + 10;
        rel_fn = realloc(rel_fn, rel_size);
      }
      strcpy(rel_fn + suff_size + 1, de->d_name);

      /* Check the file's existence */
      exists = lstat(dir_fn, &buf);
      if (exists < 0) {
        fprintf(stderr, "Couldn't stat %s\n", dir_fn);
        exit(1);
      } 

      /* Print the size of the file's name, as a four-byte integer in little endian */
      fname = strlen(rel_fn);
      fwrite(&fname, 4, 1, stdout);

      /* Print the relative filepath, no null character */ 
      fwrite(rel_fn, 1, fname,  stdout); 

      /* Print the file's inode as an eight byte long in little endian */
      fwrite(&buf.st_ino, 8, 1, stdout);

      /* If you have seen that inode before, do nothing */
      if (jrb_find_gen(inodes, new_jval_l(buf.st_ino), compare) == NULL) {
        /* Insert into the red-black tree */
        jrb_insert_gen(inodes, new_jval_l(buf.st_ino), new_jval_i(0), compare);

        /* Print the file's mode as a four byte integer in little endian */ 
        fwrite(&buf.st_mode, 4, 1, stdout);
        /* Print the file's last modification time, in seconds, as an eight byte long in little endian */
        fwrite(&buf.st_mtime, 8, 1, stdout);
         
        /* Don't make the recursive call, but instead put the directory into the dllist. */
        if (S_ISDIR(buf.st_mode)) {
         dll_append(directories, new_jval_s(strdup(dir_fn)));
        }
        else {
          /* Print the file's size as an eight byte long in little endian */ 
          fwrite(&buf.st_size, 8, 1, stdout);
          /* Open the file and error check */
          file = fopen(dir_fn, "r");
          if (file == NULL) { perror(dir_fn); exit(1); }

          /* Allocate a buffer for the file's bytes, read and write them */
          bytes = (char *) malloc(sizeof(char) * buf.st_size + 10);
          fread(bytes, 1, buf.st_size, file);
          fwrite(bytes, 1, buf.st_size, stdout); 

          fclose(file);
          free(bytes);
        }
      }
    }
  }

  /* Make the recursive calls after you've closed the directory.  */

  closedir(d);

  /* Traverse the directories */
  dll_traverse(tmp, directories) {
    /* Grab each suffix of absolute path */
    suffix = grab_path(tmp->val.s);
    sz = strlen(suffix);
    /* Reallocate and copy, using the relative path as the new prefix */
    if (rel_size < suff_size + sz + 2) {
      rel_size = suff_size + sz + 10;
      rel_fn = realloc(rel_fn, rel_size);
    }
    strcpy(rel_fn + suff_size + 1, suffix); 
    directory_traverse(tmp->val.s, inodes, rel_fn);
  }

  /* Clean up.  You need to free the strings inside the dllist, because you
     allocated them with strdup(), and they'll be a memory leak otherwise. */

  dll_traverse(tmp, directories) free(tmp->val.s);
  free_dllist(directories);
  free(dir_fn);
  free(rel_fn);
}

int main(int argc, char** argv) {
  char *pathname, *relative;
  struct stat buf;
  int psize, exists;
  JRB inodes;

  if (argc != 2) { fprintf(stderr, "./bin/tarc directory/\n"); exit(1); }

  /* Grab the pathname */
  pathname = strdup(argv[1]); 

  /* Print the directories information before first recursive call */
  exists = lstat(pathname, &buf);
  if (exists < 0) {
    fprintf(stderr, "Couldn't stat %s\n", pathname);
    exit(1);
  } 

  relative = grab_path(pathname);

  inodes = make_jrb();

  /* Print the root directory info */
  psize = strlen(relative);

  fwrite(&psize, 4, 1, stdout);
  fwrite(relative, 1, psize, stdout);
  fwrite(&buf.st_ino, 8, 1, stdout);
  fwrite(&buf.st_mode, 4, 1, stdout);
  fwrite(&buf.st_mtime, 8, 1, stdout);

  /* Insert the inode to the new tree */
  jrb_insert_gen(inodes, new_jval_l(buf.st_ino), new_jval_i(0), compare);

  /* Recursively search the directory for files and subdirectories */
  directory_traverse(pathname, inodes, relative);

  free(pathname);
  jrb_free_tree(inodes);

  return 1;
}
